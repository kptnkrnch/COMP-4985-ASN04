#include <vector>
#include <iostream>
#include <string.h>
#include <conio.h>
#include <string>
#include <sstream>
#include <map>

using namespace std;

typedef struct RoutingItem {
	string destination;
	string nexthoprouter;
	int hops;
} RoutingItem;

typedef struct Router {
	string routerName;
	vector<RoutingItem> routingTable;
} Router;

void InitializeRouters(vector<Router> * routers);
RoutingItem CreateRoutingItem(string network, string nexthoprouter, int hops);
void BroadcastRoutingTable(int routerIndex, vector<Router> * routers);
map<string, string> UpdateActiveNetworks(vector<Router> routers);

int main() {
	vector<Router> routers;
	InitializeRouters(&routers);
	map<string, string> networks;

	int i = 1;
	for (std::vector<Router>::iterator routerIterator = routers.begin(); routerIterator != routers.end(); routerIterator++) {
		for (std::vector<RoutingItem>::iterator itemIterator = routerIterator->routingTable.begin(); itemIterator != routerIterator->routingTable.end(); itemIterator++) {
			cout << "Router " << i << ": " << itemIterator->destination << " " << itemIterator->nexthoprouter << " " << itemIterator->hops << endl;
		}
		i++;
	}
	networks = UpdateActiveNetworks(routers);

	/**/
	bool isComplete = false;
	bool isFirstIteration = true;
	while (!isComplete) {
		i = 0;
		int complete = 0;

		i = 0;
		for (std::vector<Router>::iterator routerIterator = routers.begin(); routerIterator != routers.end(); routerIterator++) {
			BroadcastRoutingTable(i, &routers);
			networks = UpdateActiveNetworks(routers);
			if (routerIterator->routingTable.size() == networks.size()) {
				complete++;
			}
			i++;
		}
		if (isFirstIteration) {
			isFirstIteration = false;
			for (std::vector<Router>::iterator routerIterator = routers.begin(); routerIterator != routers.end(); routerIterator++) {
				if (routerIterator->routerName == "R1") {
					for (std::vector<RoutingItem>::iterator n = routerIterator->routingTable.begin(); n != routerIterator->routingTable.end(); n++) {
						if (n->destination == "N1") {
							routerIterator->routingTable.erase(n);
							break;
						}
					}
				}
			}
		}
		if (complete == routers.size()) {
			isComplete = true;
		}
	}
	
	cout << endl << endl;
	i = 1;
	for (std::vector<Router>::iterator routerIterator = routers.begin(); routerIterator != routers.end(); routerIterator++) {
		for (std::vector<RoutingItem>::iterator itemIterator = routerIterator->routingTable.begin(); itemIterator != routerIterator->routingTable.end(); itemIterator++) {
			cout << "Router " << i << ": " << itemIterator->destination << " " << itemIterator->nexthoprouter << " " << itemIterator->hops << endl;
		}
		i++;
	}

	_getch();

	return 0;
}

RoutingItem CreateRoutingItem(string network, string nexthoprouter, int hops) {
	RoutingItem item;

	item.destination = network;
	item.nexthoprouter = nexthoprouter;
	item.hops = hops;

	return item;
}

void InitializeRouters(vector<Router> * routers) {
	for (int i = 0; i < 6; i++) {
		Router r;
		stringstream ss;
		string network;
		string nexthop;

		ss << "N" << (i+1);
		network = ss.str();
		ss.str("");
		ss.clear();
		ss << "R" << (i+1);
		nexthop = ss.str();
		ss.str("");
		ss.clear();
		r.routingTable.push_back(CreateRoutingItem(network, nexthop, 1));

		ss << "N" << (i+2);
		network = ss.str();
		r.routingTable.push_back(CreateRoutingItem(network, nexthop, 1));
		r.routerName = nexthop;
		routers->push_back(r);
	}
}

void BroadcastRoutingTable(int routerIndex, vector<Router> * routers) {
	if (routerIndex <= routers->size() && routerIndex >= 0) {
		Router current = routers->at(routerIndex);
		Router neighbour1;
		Router neighbour2;
	
		if (routerIndex > 0) {
			neighbour1 = routers->at(routerIndex - 1);
			for (std::vector<RoutingItem>::iterator i = current.routingTable.begin(); i != current.routingTable.end(); i++) {
				bool found = false;
				for (std::vector<RoutingItem>::iterator n = neighbour1.routingTable.begin(); n != neighbour1.routingTable.end(); n++) {
					if (i->destination == n->destination) {
						found = true;
						if (i->hops < n->hops) {
							n->hops = i->hops + 1;
							n->nexthoprouter = current.routerName;
						}
					}
				}
				if (!found) {
					neighbour1.routingTable.push_back(CreateRoutingItem(i->destination, current.routerName, i->hops + 1));
				}
			}

			for (std::vector<RoutingItem>::iterator n = neighbour1.routingTable.begin(); n != neighbour1.routingTable.end(); n++) {
				if (n->nexthoprouter == current.routerName) {
					bool found = false;
					for (std::vector<RoutingItem>::iterator i = current.routingTable.begin(); i != current.routingTable.end(); i++) {
						if (n->destination == i->destination) {
							found = true;
						}
					}
					if (!found) {
						neighbour1.routingTable.erase(n);
					}
				}
			}

			routers->at(routerIndex - 1) = neighbour1;
		}

		if (routerIndex < 5) {
			neighbour2 = routers->at(routerIndex + 1);
			for (std::vector<RoutingItem>::iterator i = current.routingTable.begin(); i != current.routingTable.end(); i++) {
				bool found = false;
				for (std::vector<RoutingItem>::iterator n = neighbour2.routingTable.begin(); n != neighbour2.routingTable.end(); n++) {
					if (i->destination == n->destination) {
						found = true;
						if (i->hops < n->hops) {
							n->hops = i->hops + 1;
							n->nexthoprouter = current.routerName;
						}
					}
				}
				if (!found) {
					neighbour2.routingTable.push_back(CreateRoutingItem(i->destination, current.routerName, i->hops + 1));
				}
			}

			for (std::vector<RoutingItem>::iterator n = neighbour2.routingTable.begin(); n != neighbour2.routingTable.end(); n++) {
				if (n->nexthoprouter == current.routerName) {
					bool found = false;
					for (std::vector<RoutingItem>::iterator i = current.routingTable.begin(); i != current.routingTable.end(); i++) {
						if (n->destination == i->destination) {
							found = true;
						}
					}
					if (!found) {
						neighbour2.routingTable.erase(n);
						break;
					}
				}
			}

			routers->at(routerIndex + 1) = neighbour2;
		}
	}
}

map<string, string> UpdateActiveNetworks(vector<Router> routers) {
	map<string, string> activeNetworks;

	for (std::vector<Router>::iterator routerIterator = routers.begin(); routerIterator != routers.end(); routerIterator++) {
		for (std::vector<RoutingItem>::iterator itemIterator = routerIterator->routingTable.begin(); itemIterator != routerIterator->routingTable.end(); itemIterator++) {
			string dest = itemIterator->destination;
			activeNetworks[dest] = dest;
		}
	}

	return activeNetworks;
}