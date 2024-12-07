#!/bin/bash

File=$1

kotlinc $File.kt -include-runtime -d $File.jar
java -jar $File.jar
