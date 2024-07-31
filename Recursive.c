
processAST(node):
    if node is null:
        return
    switch node.type:
        case "NODE_CMD_LINE":
            save the operator
            processAST(node.data.cmd_line.left)
            save the status of the command line
            if the status of the left command line is 1 and the operator is an or
                set the status of the command line to 1
            else the status of the left command line is 0 and the operator is an and
                set the status of the command line to 0
            processAST(node.data.cmd_line.right)
            Save the status of the command line
            if the status of the right command line is 1 and the operator is an or
                set the status of the command line to 1
            else the status of the right command line is 0 and the operator is an and
                set the status of the command line to 0
            if the operator is an or and the status of the command line is 1
                set the status of the command line to 1
            else if the operator is an and and the status of the command line is 0
                set the status of the command line to 0
            break
        case "NODE_PIPELINE":
            while node.data.pipeline.cmd_count:
                processAST(node.data.pipeline.cmds[node.data.pipeline.cmd_count])
                Take the output of the command and save it
                put the comand in the input of the next command
                node.data.pipeline.cmd_count--
            break
        case "NODE_SIMPLE_CMD":
            processAST(current)
            send the execution of the command with all the words
            break
            //CHECK THE NEW REDIRECTION STRUCTURE

