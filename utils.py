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

def all_to_the_left(levels):
    result = 0
    for i in range(levels):
        this_pos = int((i+1)*(i+2)/2-1)
        this_val = 1<<this_pos
        result += this_val
        print_as_c_array(levels,(result))
    return result

def left_right(levels):
    result = 1
    last_pos = 0
    for i in range(1,levels):
        if (i&1):
            this_pos = last_pos + i +1
        else:
            this_pos =last_pos + i
        last_pos = this_pos
        this_val = 1<<this_pos
        result += this_val
        print_as_c_array(levels,(result))
    return result

def print_as_c_array(levels,board):
    number_of_bytes = (((levels+1)*(levels+2))>>4)-1
    output = "{"
    for i in range(number_of_bytes):
        output = output + hex(((board)>>(i*8))&0xff)+", "
    output = output[:-1] + "},"
    print(output)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Print a Galton board.')
    parser.add_argument('levels', type=int, help='Number of levels in the Galton board')
    args = parser.parse_args()
    print_galton(args.levels,left_right(10))
