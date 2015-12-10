#! /bin/sh
if [ "$1" = "BG" ] ; then
    trap "echo haha; sleep 20;echo trap sleep done" 15
    sleep 100
    exit
fi
MARKER=`dirname $0`@$$
export MARKER
echo "MARKER=$MARKER"
$0 BG &

`dirname $0`/chp.pl $$ &
sleep 20
echo "done"

