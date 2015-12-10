#! /usr/bin/env perl
use strict;
my $cmdpid=$ARGV[0];
my $ppid=getppid();
if ( $cmdpid <= 1) {
    print STDERR "invalid pid on commandline: $cmdpid, exiting\n";
    exit
}
if ($ppid <= 1){
    print STDERR "invalid ppid $ppid, exiting\n";
    exit
}
my $marker=$ENV{'MARKER'};
if (  $marker eq "") {
    print STDERR "marker MARKER not found in env\n";
    exit
}
while (1){
    my $rt=0;
    if ($cmdpid == $ppid){
        $rt=kill(0,$ppid);
        print "parent $ppid status=$rt\n";
    }
    else{
        print "parent pid $ppid does not match pid from commandline $cmdpid, cleaning up\n";
    }
    if ($rt <= 0){
        print "PARENT $cmdpid exited, cleaning up\n";
        for my $proc (glob("/proc/[0-9]*")){
            my $pid=$proc;
            $pid=~s?.*/??;
            $/="\0";
            my $ef=$proc."/environ";
            if (-r $ef && $pid != $$ ){
                open(my $h,"<",$ef);
                if ($h){
                    while(<$h>){
                        chomp;
                        my ($n,$v)=split(/=/,$_,2); 
                        if ($n eq "MARKER" && $v eq $marker){
                            print "found marked process $pid, killing it\n";
                            kill 15,$pid;
                        }
                    }
                    close($h);
                }
            }
        }
        sleep(1);
        print "monitor exiting\n";
        exit(0);
    }   
    sleep(1)
}
