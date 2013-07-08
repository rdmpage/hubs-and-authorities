# $Id: Makefile.am,v 1.2 2005/04/18 23:02:08 rdmp1c Exp $

GRAPHDIR	= graph
LIBS		= -lGTL -L$(GRAPHDIR) -lgraph 
INCLUDES 	= -I$(GRAPHDIR) 

AM_CXXFLAGS=-Wno-deprecated
AM_CFLAGS=-Wno-deprecated

SUBDIRS = graph

# The actual programs
bin_PROGRAMS = hits
hits_SOURCES = hits.cpp
