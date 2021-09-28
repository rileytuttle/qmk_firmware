#!/usr/bin/env python3

import re
import argparse

def get_layers(args):
    with open(f"keyboards/{args.keyboard}/keymaps/{args.keymap}/keymap.c", "r") as f:
        if len(args.layers) > 0:
            if args.layers[0] == "all":
                printing = False
                for line in f.readlines():
                    match = re.match(f"\/\* (\S+)$", line)
                    if match is not None:
                        printing = True
                    if printing:
                        print(line.rstrip())
                        match = re.match(f" \*\/$", line)
                        if match is not None:
                            printing = False
            else:
                printing = False
                for line in f.readlines():
                    for layer in args.layers:
                        match = re.match(f"\/\* {layer}$", line)
                        if match is not None:
                            printing = True
                    if printing:
                        print(line.rstrip())
                        match = re.match(f" \*\/$", line)
                        if match is not None:
                            printing = False
        else:
            for line in f.readlines():
                match = re.match(f"\/\* (\S+)$", line)
                if match is not None:
                    print(match.group(1))

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
    parser.add_argument("--layers", "-l", action="append", default=[], help="layer to print out. default is print the layer names")

    args = parser.parse_args()

    layer_list = get_layers(args)

if __name__ == "__main__":
    main()
