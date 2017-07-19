import pylab as p
import networkx as nx

G = nx.Graph()
G.add_edge("A","B")
G.add_edge("A","H")
G.add_edge("H","C")
G.add_edge("B","C")
G.add_edge("B","D")
G.add_edges_from([(1,2,{'color':'blue'}), (2,3,{'weight':8})])

G.add_node(1)

nx.draw(G)
p.show()