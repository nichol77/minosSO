#############################################################################
## Makefile -- New Version of my Makefile that works on both linux
##              and mac os x
## Ryan Nichol <rjn@hep.ucl.ac.uk>
##############################################################################
include Makefile.arch

#Site Specific  Flags
SYSINCLUDES	=
SYSLIBS         = -L /home/rjn/thirdParty/lib -l profiler 
DLLSUF = ${DllSuf}
OBJSUF = ${ObjSuf}
SRCSUF = ${SrcSuf}

#Generic and Site Specific Flags
CXXFLAGS     += $(ROOTCFLAGS)  $(SYSINCLUDES) -I /home/rjn/minos/ccPlusNc/ -I /Users/rjn/minos/ccPlusNc/
LDFLAGS      += -g $(ROOTLDFLAGS) 


LIBS          = $(ROOTLIBS)  $(SYSLIBS) 
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

PROGRAMS=doGridSearchFake doGridSearchFakeExp doGridSearchFakeOnePoint makeFakeSurfaceFiles makeFinalPlots addFinalPlots doGridSearchReal

all : ${PROGRAMS}




doGridSearchReal : $(ROOT_LIBRARY) doGridSearchReal.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) doGridSearchReal.$(SRCSUF)  $(LIBS) -o $@

doGridSearchFake : $(ROOT_LIBRARY) doGridSearchFake.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) doGridSearchFake.$(SRCSUF)  $(LIBS) -o $@

doGridSearchFakeExp : $(ROOT_LIBRARY) doGridSearchFakeExp.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) doGridSearchFakeExp.$(SRCSUF)  $(LIBS) -o $@

doGridSearchFakeOnePoint : $(ROOT_LIBRARY) doGridSearchFakeOnePoint.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) doGridSearchFakeOnePoint.$(SRCSUF)  $(LIBS) -o $@


makeFakeSurfaceFiles : $(ROOT_LIBRARY) makeFakeSurfaceFiles.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) makeFakeSurfaceFiles.$(SRCSUF)  $(LIBS) -o $@


makeFinalPlots : $(ROOT_LIBRARY) makeFinalPlots.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) makeFinalPlots.$(SRCSUF)  $(LIBS) -o $@

addFinalPlots : $(ROOT_LIBRARY) addFinalPlots.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) addFinalPlots.$(SRCSUF)  $(LIBS) -o $@



%.$(OBJSUF) : %.$(SRCSUF)
	@echo "<**Compiling**> "$<
	$(CXX) $(CXXFLAGS) -c $< -o  $@

%.$(OBJSUF) : %.C
	@echo "<**Compiling**> "$<
	$(CXX) $(CXXFLAGS) $ -c $< -o  $@


eventDict.C: $(CLASS_HEADERS)
	@echo "Generating dictionary ..."
	@ rm -f *Dict* 
	rootcint $@ -c $(CLASS_HEADERS) LinkDef.h


clean:
	@rm -f *Dict*
	@rm -f *.${OBJSUF}
	@rm -f $(subst .$(DLLSUF),.so,$(ROOT_LIBRARY))	
	@rm -f ${PROGRAMS}
#############################################################################



