sumKnot: auto-knotSums.cpp knot.cpp rrem.cpp
	${CXX} $? -o $@

echKnot: auto-knots.cpp knot.cpp rrem.cpp
	${CXX} $? -o $@

clean:
	-rm *.exe