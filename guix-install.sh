#!/bin/sh
guix environment engstrand-dsblocks --ad-hoc pkg-config -- make clean install PREFIX=~/.local CC=gcc
