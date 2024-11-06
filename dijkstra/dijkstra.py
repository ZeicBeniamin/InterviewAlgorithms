import queue
import sys

# Forward declaration
class Node:
    pass


class Edge:
    def __init__(self, to_node: Node, weight: int):
        if not isinstance(to_node, Node):
            raise Exception("Expected 'to_node' argument to be of type Node")
        self.to_node = to_node
        self.weight = weight


class Node:
    def __init__(self, id: int):
        if not isinstance(id, int):
            raise Exception("'id' variable shoud be of type int")
        self.id = id
        self.edges = []
        self.min_dist = sys.maxsize
        self.visited = False

    def add_edge(self, node: Node, weight: int):
        edge = Edge(node, weight)
        self.edges.append(edge)

    def __lt__(self, other):
        return self.min_dist < other.min_dist

    def __eq__(self, other):
        return self.min_dist == other.min_dist


nodes_dict = {}

def dijkstra(start, nodes_num):
    nodes_queue = queue.PriorityQueue()

    nodes_queue.put(nodes_dict[start])
    nodes_dict[start].min_dist = 0

    while not nodes_queue.empty():
        curr_node = nodes_queue.get()

        if curr_node.visited:
            continue

        for edge in curr_node.edges:
            next_node = edge.to_node
            next_edge_distance = edge.weight

            potential_distance = curr_node.min_dist + next_edge_distance
            if next_node.min_dist >= potential_distance:
                next_node.min_dist = potential_distance

            nodes_queue.put(next_node)

        curr_node.visited = True

def read():
    nodes = 0
    with open("dijkstra.in", "r") as file:
        first_line = file.readline()
        nodes, _ = [int(elem) for elem in first_line.split()]
        # Init all nodes:
        for i in range(1, int(nodes)):
            nodes_dict[i] = Node(i)

        for line in file:
            from_node, to_node, weight = line.split(" ")

            from_node = int(from_node)
            to_node = int(to_node)
            weight = int(weight)

            if from_node not in nodes_dict:
                nodes_dict[from_node] = Node(from_node)
            if to_node not in nodes_dict:
                nodes_dict[to_node] = Node(to_node)

            nodes_dict[from_node].add_edge(nodes_dict[to_node], weight)

    return nodes

def write(nodes_num):
    with open("pydijkstra.out", "w") as outfile:
        for key in range(2, nodes_num + 1):
            node = nodes_dict[key]
            if node.min_dist == sys.maxsize:
                outfile.write(f"0 ")
            else:
                outfile.write(f"{node.min_dist} ")

def main():
    nodes_num = read()
    dijkstra(start=1, nodes_num=nodes_num)
    write(nodes_num)


if __name__ == "__main__":
    main()
