hubs-and-authorities
====================

C++ implementation of hubs and authorities (HITS) and PageRank algorithms


Given a GML graph where nodes represent papers and edges represent the 
relationship "cites", we compute the authority and hub values for each node
based on Jon Kleinberg's "Authoritative sources in a hyperlinked environment"
(Authoritative sources in a hyperlinked environment)[http://doi.acm.org/10.1145/324133.324140].
The results are dumped as a tab-delimited list.

Pagerank algorithm based on http://www.ianrogers.net/google-page-rank/

#### Dependencies
The program uses the Graph Template Library (GTL) which is available from [http://www.fim.uni-passau.de/fileadmin/files/lehrstuhl/brandenburg/projekte/gtl/GTL-1.2.4-lgpl.tar.gz](http://www.fim.uni-passau.de/fileadmin/files/lehrstuhl/brandenburg/projekte/gtl/GTL-1.2.4-lgpl.tar.gz)

#### Building
If you are building from this repository you will need to do the standard things:

* aclocal
* autoconf
* automake
* ./configure
* make

#### Example

The examples folder contains citation graph for an ant specimen and various entities (DNA sequences, images, publications) that "cite" that specimen:

![Example](https://github.com/rdmpage/hubs-and-authorities/raw/master/examples/CASENT0106070.png)

Running the program on this graph

* matching examples/CASENT0106070.gml

produces a text dump of PageRank values.

	Graph read from file "examples/CASENT0106070.gml" has 10 nodes and 20 edges
	Node	Page rank
	CASENT0106070	1.25722
	AY703487	0.194147
	AY703554 	0.194147
	AY703621 	0.194147
	AY703688	0.194147
	AY703755 	0.194147
	EF013219	0.165938
	EF013381	0.165938
	doi:10.1111/j.1365-3113.2004.00281.x	0.165938
	pmdi:17079492	0.15


