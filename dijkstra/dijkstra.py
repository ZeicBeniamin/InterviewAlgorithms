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

    distances = dict()
    
    def __init__(self, id: int):
        if not isinstance(id, int):
            raise Exception("'id' variable shoud be of type int")
        self.id = id
        self.edges = []
        self._min_dist = sys.maxsize
        Node.distances[id] = sys.maxsize
        self.visited = False

    def add_edge(self, node: Node, weight: int):
        edge = Edge(node, weight)
        self.edges.append(edge)

    def set_min_dist(self, min_dist):
        self._min_dist = min_dist
        Node.distances[self.id] = min_dist
    
    def min_dist(self):
        if self._min_dist != Node.distances[self.id]:
            raise Exception("Difference between member variable and class variable")
        return Node.distances[self.id]

    def __lt__(self, other):
        return Node.distances[self.id] < Node.distances[other.id]

    def __eq__(self, other):
        return Node.distances[self.id] == Node.distances[other.id]


nodes_dict = {}

def dijkstra(start, nodes_num):
    # Something somewhere (maybe in the priority queue) generates non-minimum
    # results for the grader10 test from infoarena
    nodes_queue = queue.PriorityQueue()

    nodes_queue.put(nodes_dict[start])
    nodes_dict[start].set_min_dist(0)

    itercount = 0
    last_weight = 0

    z = 30

    while not nodes_queue.empty():
        itercount += 1
        curr_node = nodes_queue.get()

        # if itercount > 15461 - z and itercount < 15461 + z:
            # print(f"[4] Picked {curr_node.id}; visited {curr_node.visited}; id {id(curr_node)}")

        if itercount > 15461 - z and itercount < 15461 + z:
            print(f"{curr_node.id}  \t\t{curr_node.min_dist()}", end="")

        if curr_node.visited:
            # if itercount > 15461 - z and itercount < 15461 + z:
            #     print(f"[3] Node {curr_node.id} - visited   \t\t\t\tDist: {curr_node.min_dist()}; iter: {itercount}")
            if itercount > 15461 - z and itercount < 15461 + z:
                print(f" ++++++++++")
            continue
        if itercount > 15461 - z and itercount < 15461 + z:
            print(f"")

        if last_weight > curr_node.min_dist():
            print(f"Storing! Last w. {last_weight} curr: {curr_node.min_dist()}")


        # if itercount > 15461 - z and itercount < 15461 + z:
        #     print(f"[0] Node {curr_node.id}.   \tDist: {curr_node.min_dist()}; iter: {itercount}")

        for edge in curr_node.edges:
            next_node = edge.to_node
            next_edge_distance = edge.weight

            potential_distance = curr_node.min_dist() + next_edge_distance
            if next_node.visited:
                if next_node.min_dist() > potential_distance:
                    # print(f"[1] Node {next_node.id} already visited. Old dist: {next_node.min_dist()}, new: {potential_distance}; iter: {itercount}")
                    print(f"\t{next_node.id} \t{next_node.min_dist()} \t+{potential_distance} ---- ")
                    next_node.set_min_dist(potential_distance)
                continue

            if next_node.min_dist() > potential_distance:
                # if next_node.visited:
                #     print(f"[2] Node {next_node.id} already visited. Old dist: {next_node.min_dist()}, new: {potential_distance}; iter: {itercount}")
                next_node.set_min_dist(potential_distance)
                # if itercount > 15461 - z and itercount < 15461 + z:
                    # print(f"\t{next_node.id} \t+{potential_distance}")
            # else:
                # if itercount > 15461 - z and itercount < 15461 + z:
                    # print(f"\t{next_node.id} \t+{next_node.min_dist()}")

            nodes_queue.put(next_node)
        last_weight = curr_node.min_dist()

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
            if node.min_dist() == sys.maxsize:
                outfile.write(f"0 ")
            else:
                outfile.write(f"{node.min_dist()} ")

def main():
    nodes_num = read()
    dijkstra(start=1, nodes_num=nodes_num)
    write(nodes_num)


if __name__ == "__main__":
    main()
