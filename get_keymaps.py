#!/usr/bin/env python3

import re
import argparse

def get_all_layers(args):
    ret_list = []
    with open(f"keyboards/{args.keyboard}/keymaps/{args.keymap}/keymap.c", "r") as f:
        for line in f.readlines():
            match = re.match(f"\/\* (\S+)$", line)
            if match is not None:
                ret_list.append(match.group(1))
    return ret_list

def get_layers(args):
    ret_list = args.layers
    if len(args.layers) == 0:
        ret_list = get_all_layers(args)
    elif args.layers[0] == "all":
        ret_list = get_all_layers(args)
    return ret_list

def print_layers(args, layer_list):
    with open(f"keyboards/{args.keyboard}/keymaps/{args.keymap}/keymap.c", "r") as f:
        printing = False
        for line in f.readlines():
            for layer in layer_list:
                match = re.match(f"\/\* {layer}$", line)
                if match is not None:
                    printing = True
            if printing:
                print(line.rstrip())
                match = re.match(f" \*\/$", line)
                if match is not None:
                    printing = False

def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter,
                                     description="This script will decode keymaps",
                                     epilog="""
    EXAMPLES:
        ./get_keymaps.py example1
        ./get_keymaps.py example2
        ./get_keymaps.py example3
    """)
    parser.add_argument("--keymap", "-km", default="rileytuttle", help="default keymap is rileytuttle")
    parser.add_argument("--keyboard", "-kb", default="preonic", help="default keymap is preonic/rev3")
    parser.add_argument("--layers", "-l", nargs="+", default=[], help="layer to print out. default is print the layer names")

    args = parser.parse_args()

    layer_list = get_layers(args)
    if len(args.layers) == 0:
        for layer in layer_list:
            print(layer)
    else:
        print_layers(args, layer_list)

if __name__ == "__main__":
    main()
