import sys
import os
import argparse


def handle_head(file: str, _n: int = 10) -> None:
    with open(file, "r") as f:
        while _n > 0:
            # print(f.readline())
            line: str = f.readline()
            print(line, end="")
            _n = _n - 1


def handle_tail(file: str, _n: int = 10) -> None:
    lines: list[str] = []
    with open(file, "r") as f:
        lines = f.readlines()

    for line in lines[-_n:]:
        print(line, end="")


def handle_pwd() -> None:
    print(os.getcwd())


def handle_wc(filename: str) -> None:

    lines: int = 0
    words: int = 0
    chars: int = 0

    inside_word: bool = False

    with open(filename, "r") as f:
        while True:
            char: str = f.read(1)
            if not char:
                break
            chars += 1
            if char == "\n":
                lines += 1
            if not inside_word:
                words += 1
                inside_word = True

            # print(char)

    print(lines, words, chars, filename)


def main():
    # parser = argparse.ArgumentParser(
    #     prog="uutils",
    #     description="Re-implements some Unix shell commands",
    # )

    # sub_parser = parser.add_subparsers(
    #     dest="subcommand", help="Unix shell commands that are implemented i.e. wc, head"
    # )

    # # parser_wc = sub_parser.add_parser("wc", help="wc <filename>")
    # # parser_head = sub_parser.add_parser("head", help="head [OPTIONS] <filename>")

    # wc_subparser = sub_parser.add_parser("wc", help="wc [OPTIONS] <filename>")
    # wc_subparser.add_argument("-f", "--files", required=True, help="File to work on")
    # wc_subparser.set_defaults(function=handle_head)

    # args = parser.parse_args()

    # print()
    # parser.print_help()
    # print(args)

    parser = argparse.ArgumentParser(
        prog="cutils", description="Re-implementes some Unix shell commands"
    )

    sub_parser = parser.add_subparsers(
        dest="subcommand", help="Unix shell commands that are implemented"
    )
    parser_wc = sub_parser.add_parser("wc", help="wc <filename>")
    parser_wc.add_argument("-l", help="Print number of lines", required=False, type=str)
    parser_wc.add_argument("-w", help="Print number of words", required=False, type=str)
    parser_wc.add_argument(
        "-c", help="Print number of characters", required=False, type=str
    )
    parser_wc.add_argument("-f", "--file", help="Filename", required=True)

    parser_head = sub_parser.add_parser("head", help="head [OPTIONS] <filename>")
    parser_head.add_argument(
        "-n", help="Number of lines to print", default=10, required=False
    )
    parser_head.add_argument("-f", "--file", help="Filename", required=True)

    parser_tail = sub_parser.add_parser("tail", help="tail [OPTIONS] <filename>")
    parser_tail.add_argument(
        "-n", help="Number of lines to print", type=int, default=10, required=False
    )
    parser_tail.add_argument("-f", "--file", help="Filename", required=True)

    parser_pwd = sub_parser.add_parser(
        "pwd",
        help="Print present working directory",
    )

    args = parser.parse_args()

    if args.subcommand == "wc":
        # print("wc")
        handle_wc(args.file)
        pass
    elif args.subcommand == "head":
        # print("head")
        handle_head(args.file)
    elif args.subcommand == "pwd":
        handle_pwd()
    # print(sys.argv[1:])
    # print(type(sys.argv[1:]))
    # print(str(sys.argv[3]))
    # print(type(str(sys.argv[3])))
    # print(str(sys.argv[2]))
    # print(type(str(sys.argv[2])))

    # handle_head(file=str(sys.argv[3]), _n=abs(int(sys.argv[2])))
    # handle_tail(file=str(sys.argv[3]), _n=abs(int(sys.argv[2])))
    # handle_head(file=str(sys.argv[2]))

    # handle_head(str(sys.argv[1:3]))


if __name__ == "__main__":
    main()
