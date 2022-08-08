import os
import networkx as nx
import pygraphviz
from networkx.drawing.nx_agraph import write_dot
import matplotlib.pyplot as plt
import copy
import sys

code = [2,2,7,7,1,5,3,1,1,4,4,5]
#code = [1,8,3,1,4,4,8]
def getGraphList(code):
    graphlist = []
    n = len(code) + 2
    drawn_nodes = []
    G = nx.Graph()
    copycode = code
    node2list = []
    for node in code:
        for node2 in range(1,n+1):
            if node2 not in code and node2 not in node2list:
                G.add_edge(node, node2)
                code = code[1:]
                node2list.append(node2)
                graphlist.append(copy.deepcopy(G))
                break
    
    finalnodes = []

    for node in range(1,n+1):
        try:
            deg = G.degree[node]
        except:
            deg = 0
        f = 0
        for node2 in copycode:
            if node == node2:
                f += 1
        if deg < f+1:
            finalnodes.append(node)
        
    G.add_edge(finalnodes[0], finalnodes[1])
    graphlist.append(G)
    node2list.append(r")$\\ Die letze Kante ergibt sich aus $f_i = d_i-1$, in diesem Fall: $(" + str(finalnodes[0]) + "," + str(finalnodes[1]))
    return graphlist, node2list

def write_to_frame(framename, code):
    graphlist, node2list = getGraphList(code)
    importantlines = [r"\begin{frame}" + "\n"]
    name = "cayley_animation"
    if not os.path.exists(name):
        os.mkdir(name)
    parentpath = os.getcwd()
    os.chdir(name)
    codestring = "$(a_1, \dots, a_{n-2}) = (" + str(code[0])
    for node in code[1:]:
        codestring+= "," + str(node)
    codestring += ")$"
    for index, graph in enumerate(graphlist):
        currentbstring = "$(b_1, \dots, b_i) = ("
        for node in node2list[:index+1]:
            currentbstring += str(node) + ","
        currentbstring = currentbstring[:-1] + ")$"
        
        for node in graph.nodes:
            graph.nodes[node]["style"] = "vertex"
        for edge in graph.edges:
            graph.edges[edge]["style"] = "edge"
        filename = 'graph' + str(index) + '.dot'
        filenametikz = 'graph' + str(index) + '.tex'
        write_dot(graph, filename)
        os.system(f"dot -Txdot {filename} | dot2tex -ftikz -tmath --figonly -s --nodeoptions scale=0.5> {filenametikz}") #--nodeoptions scale=0.5
        importantlines.append(f"\\only<{index+1}>" + "{\n")
        importantlines.append(codestring + r"\\")
        importantlines.append(currentbstring)#description of what is happening
        importantlines.append(r"\input{" + name + "/" + filenametikz + "}\n")
        importantlines.append(r"\hfill")
        importantlines.append("}\n")
    importantlines.append(r"\end{frame}")
    os.chdir(parentpath)
    with open(framename, "w") as f:
        f.writelines(importantlines)

write_to_frame("cayley_animation_frame.tex", code)