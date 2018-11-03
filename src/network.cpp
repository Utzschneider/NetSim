#include "network.h"
#include <iostream>
#include <algorithm>
#include "random.h"


void Network::resize(const size_t &n){
	values.clear();
	values.resize(n);
	for (int i(0); i<n ; ++i) {
		values[i]= RNG.uniform_double();
	}
}

bool Network::add_link(const size_t& a, const size_t& b){
	if (a!=b and a<size() and b<size() and b!= links.find(a)->second and a!=links.find(b)->second) {
		links.insert(std::make_pair(a,b));
		links.insert(std::make_pair(b,a));
		return true ;}
	else {return false;}
}

size_t Network::random_connect(const double& mean){
	links.clear();
	std::vector<size_t> nodes (size());
	RNG.shuffle(nodes);
	int k(0);
	for (int j(0) ; j < size() ; ++j) {
		int nb_voisins (0);
		int i(0);
		do{
			if (add_link(i,j)){++nb_voisins;}
			++i;
		}while(nb_voisins<RNG.poisson(mean));
		k+=RNG.poisson(mean);
	}
	return k;
}

size_t Network::set_values(const std::vector<double>& new_values){
	values = new_values ;
	return new_values.size() ;
}

size_t Network::size() const {
	return values.size();
}

size_t Network::degree(const size_t &_n) const {
	return links.count(_n);
}

double Network::value(const size_t &_n) const {
	return values[_n] ;
}

std::vector<double> Network::sorted_values() const {
	std::vector<double> sorted_values (values);
	std::sort(sorted_values.begin(), sorted_values.end());
	std::reverse(sorted_values.begin(), sorted_values.end());
	return sorted_values;
}

std::vector<size_t> Network::neighbors(const size_t& n) const {
	std::vector<size_t> voisins;
	std::pair <std::multimap<size_t,size_t>::const_iterator, std::multimap<size_t,size_t>::const_iterator> ret;
    ret = links.equal_range(n);
    for (std::multimap<size_t,size_t>::const_iterator it=ret.first; it!=ret.second; ++it){
		voisins.push_back(it->second);
	}
	return voisins ;
}

