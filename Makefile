driver:  business.o business_arr.o driver.o ReadFile.o formulas.o helpers.o graph.o 
	g++ -g -Wall business.o business_arr.o driver.o ReadFile.o formulas.o helpers.o graph.o /usr/local/cs/cs251/react.o -lcurl -o driver

business.o:  business.cpp business.h helpers.h
	g++ -g -Wall -c business.cpp

business_arr.o:  business_arr.cpp business_arr.h formulas.h business.h helpers.h graph.h
	g++ -g -Wall -c business_arr.cpp

ReadFile.o:  ReadFile.cpp ReadFile.h formulas.h business.h helpers.h graph.h
	g++ -g -Wall -c ReadFile.cpp

formulas.o: formulas.cpp formulas.h
	g++ -g -Wall -c formulas.cpp

helpers.o:  helpers.cpp helpers.h
	g++ -g -Wall -c helpers.cpp

graph.o:  graph.cpp graph.h ReadFile.h 
	g++ -g -Wall -c graph.cpp

driver.o:  driver.cpp business_arr.h business.h ReadFile.h formulas.h helpers.h graph.h
	g++ -g -Wall -c driver.cpp

clean:
	rm -f *.o driver