package de.wellenvogel.btest
import org.gradle.api.DefaultTask
import org.gradle.api.tasks.TaskAction



class TestTask extends DefaultTask{

    @TaskAction
    public void exec(){
        println "TestTask class running"
    }


}