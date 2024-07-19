import argparse
def print_galton(levels, board = 0):
    output = ""
    position = int(levels*(levels+1)/2)
    for lev in range(levels,0,-1):
        base = ""+" "*((levels-lev)*2)
        branches = ""+" "*(((levels-lev)*2))
        for _ in range(lev):
            branches += " / \\"
            base += "e   "
        output = branches + "\n" + base+"e\n"+output
    
    output = " "*(2 * levels )+"e\n"+output
    counter = 0
    for char in output:
        if char == "e":
            if (board>>counter)&1:
                output = output.replace("e","x",1)
            else:
                output = output.replace("e","_",1)
            counter +=1
    print(output)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Print a Galton board.')
    parser.add_argument('levels', type=int, help='Number of levels in the Galton board')
    parser.add_argument('trash', type=str, help='Character to be descarted')
    parser.add_argument('board', type=str, help='Character to use for the board positions')
    args = parser.parse_args()
    print(args.board)
    for char in (args.board):
        print(char)
    print_galton(args.levels, args.board)
