#############################################################################
## Makefile -- New Version of my Makefile that works on both linux
##              and mac os x
## Ryan Nichol <rjn@hep.ucl.ac.uk>
##############################################################################
include Makefile.arch

#Site Specific  Flags
SYSINCLUDES	=
SYSLIBS         = -L /home/rjn/thirdParty/lib -l profiler -l tcmalloc 
DLLSUF = ${DllSuf}
OBJSUF = ${ObjSuf}
SRCSUF = ${SrcSuf}

#Generic and Site Specific Flags
CXXFLAGS     += $(ROOTCFLAGS)  $(SYSINCLUDES) -I /home/rjn/minos/ccPlusNc/
LDFLAGS      += -g $(ROOTLDFLAGS) 


LIBS          = $(ROOTLIBS)  $(SYSLIBS) 
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)


OBJECTS = OscCalc.o NuDstLooper.o


all : makePredictionsMultiFile addPredictionsFiles makePassTreeMultiFile


makePredictionsMultiFile : $(OBJECTS) makePredictionsMultiFile.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) makePredictionsMultiFile.$(SRCSUF) $(OBJECTS)  $(LIBS) -o $@

makePassTreeMultiFile : $(OBJECTS) makePassTreeMultiFile.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) makePassTreeMultiFile.$(SRCSUF) $(OBJECTS)  $(LIBS) -o $@


addPredictionsFiles : $(OBJECTS) addPredictionsFiles.$(SRCSUF)
	@echo "<**Compiling**> "  
	$(LD)  $(CXXFLAGS) $(LDFLAGS) addPredictionsFiles.$(SRCSUF) $(OBJECTS)  $(LIBS) -o $@




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
	@rm -f makePredictionsMultiFile
	@rm -f addPredictionsFiles
#############################################################################



