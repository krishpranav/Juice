#!/usr/bin/python
# -*- coding: utf-8 -*-

# imports
import sys
import argparse
import re
import os

template_args = {}
input_path = ""

def process_command(name, value):
    if name == "ARG":
        print("Appending arg: " + value)
        return template_args[value]
    elif name == "FILE":
        file_path = os.path.join(input_path, value)
        print("Appending file: " + value)
        with open(file_path, "r") as file:
            res = "//FILE_START:" + value + "\n"
            res += file.read()
            res += "//FILE_END"
            return res

