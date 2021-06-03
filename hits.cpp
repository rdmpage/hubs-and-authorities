// $Id:  $

// Pagerank and hits-authorities scores for a graph


//
// Given a GML graph where nodes represent papers and edges represent the 
// relationship "cites", we compute the authority and hub values for each node
// based on Jon Kleinberg's "Authoritative sources in a hyperlinked environment"
// (http://doi.acm.org/10.1145/324133.324140). The results are dumped as a 
// tab-delimited list. Algorithm based on Wikipedia article 
// https://en.wikipedia.org/wiki/HITS_algorithm
//
// Pagerank algorithm based on http://www.ianrogers.net/google-page-rank/
//

/*
@article{324140,
 author = {Jon M. Kleinberg},
 title = {Authoritative sources in a hyperlinked environment},
 journal = {J. ACM},
 volume = {46},
 number = {5},
 year = {1999},
 issn = {0004-5411},
 pages = {604--632},
 doi = {http://doi.acm.org/10.1145/324133.324140},
 publisher = {ACM Press},
 address = {New York, NY, USA},
 }
*/


#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

// http://stackoverflow.com/questions/554063/how-do-i-print-a-double-value-with-full-precision-using-cout
#include <limits>
typedef std::numeric_limits< double > dbl;


#include <GTL/GTL.h>
#include <GTL/components.h>

#include "mygraph.h"



int main (int argc, const char * argv[]) 
{
	if (argc < 2)
	{
		cout << "Usage: hits <file-name>" << endl;
		exit(1);
	}
	char filename[256];
	strcpy (filename, argv[1]);

  	// ---------------------------------------------------------	
  	// Read graph	

 	MyGraph G;
	
	GML_error err  = G.load (filename);
	if (err.err_num != GML_OK)
	{
		cerr << "Error (" << err.err_num << ") loading graph from file \"" << filename << "\"";
		switch (err.err_num)
		{
			case GML_FILE_NOT_FOUND: cerr << "A file with that name doesn't exist."; break;
			case GML_TOO_MANY_BRACKETS: cerr << "A mismatch of brackets was detected, i.e. there were too many closing brackets (])."; break;
			case GML_OPEN_BRACKET: cerr << "Now, there were too many opening brackets ([)";  break;
			case GML_TOO_MANY_DIGITS: cerr << "The number of digits a integer or floating point value can have is limited to 1024, this should be enough :-)";  break;
			case GML_PREMATURE_EOF: cerr << "An EOF occured, where it wasn't expected, e.g. while scanning a string."; break;
			case GML_SYNTAX: cerr << "The file isn't a valid GML file, e.g. a mismatch in the key-value pairs."; break;
			case GML_UNEXPECTED: cerr << "A character occured, where it makes no sense, e.g. non-numerical characters"; break;
			case GML_OK: break;
		}
		cerr << endl;
		exit(1);
	}
	else
	{
		cout << "Graph read from file \"" << filename << "\" has " << G.number_of_nodes() << " nodes and " << G.number_of_edges() << " edges" << endl;
	}
	
	
	if (0)
	{
		// Page rank
		node_map<double> page_rank (G, 0.0);
		double damp = 0.85;
		double norm = 1 - damp;
		
		int k = 40;
		for (int i = 0; i < k; i++)
		{
			node p;
			forall_nodes (p, G)
			{					
				double vote = 0.0;
				
				// Each incoming edge has a "vote"
				node::in_edges_iterator it = p.in_edges_begin();
				node::in_edges_iterator end = p.in_edges_end();
				while (it != end)
				{
					node q = p.opposite(*it);
					
					// q has an edge to p, and a vote
					// weighted by the number of edges leaving q
					vote += page_rank[q] / (double)q.outdeg();
					it++;
				}
				
				page_rank[p] = norm + damp * vote;
			}
		}		
		
		// Results
		cout << "Node\tPage rank" << endl;
		node n;
		forall_nodes (n, G)
		{
			cout << G.get_node_label(n) << "\t" << std::fixed << std::setprecision(3) << page_rank[n]  << endl;
		}

	}
	else
	{
		// Hits	
		node_map<double> authority_weight (G, 1.0);
		node_map<double> hub_weight (G, 1.0);
		
		double norm;
		
		int k = 1;
		for (int i = 0; i < k; i++)
		{
			norm = 0.0;
		
			// Authority
			//cout << "--------------Auth-----------------" << endl;
			node p;
			forall_nodes (p, G)
			{
				//cout << G.get_node_label(p) << ":";
				authority_weight[p] = 0.0;
				
				node::in_edges_iterator it = p.in_edges_begin();
				node::in_edges_iterator end = p.in_edges_end();
				while (it != end)
				{
					node q = p.opposite(*it);
					
					authority_weight[p] += hub_weight[q];
					
					//cout << q << " ";
					it++;
				}
				//cout << endl;
				norm += (authority_weight[p] * authority_weight[p]); 
			}
			
			norm = sqrt(norm);
			forall_nodes (p, G)
			{
				authority_weight[p] = authority_weight[p] / norm;
			}

			norm = 0.0;
			forall_nodes (p, G)
			{
				hub_weight[p] = 0.0;

				node::out_edges_iterator it = p.out_edges_begin();
				node::out_edges_iterator end = p.out_edges_end();
				while (it != end)
				{
					node q = p.opposite(*it);
					
					hub_weight[p] += authority_weight[q];

					//cout << q << " ";
					it++;
				}
				norm += (hub_weight[p] * hub_weight[p]);
			}

			norm = sqrt(norm);
			forall_nodes (p, G)
			{
				hub_weight[p] = hub_weight[p] / norm;
			}
	
			
		}
		
		// Results
		cout << "Node\tAuthority\tHub" << endl;
		node n;
		forall_nodes (n, G)
		{
			cout << G.get_node_label(n) 
				<< "\t" << std::fixed << std::setprecision(3) << authority_weight[n] 
				<< "\t" << std::fixed << std::setprecision(3) << hub_weight[n] 
				<< endl;
		}
	}
	
	return 0;
}
