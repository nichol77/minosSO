#############################################################################
## Makefile -- New Version of my Makefile that works on both linux
##              and mac os x
## Ryan Nichol <rjn@hep.ucl.ac.uk>
##############################################################################
include Makefile.arch

CCPLUSNC_DIR = /Users/rjn/minos/ccPlusNc
CCPLUSNC_INC_DIR =${CCPLUSNC_DIR}/include
CCPLUSNC_LIB_DIR =${CCPLUSNC_DIR}/lib

#Site Specific  Flags
SYSINCLUDES	=
SYSLIBS         = 
DLLSUF = ${DllSuf}
OBJSUF = ${ObjSuf}
SRCSUF = ${SrcSuf}

#Generic and Site Specific Flags
ATNUINCLUDES =  -I${CCPLUSNC_DIR}
CXXFLAGS     += $(ROOTCFLAGS)  $(SYSINCLUDES) $(ATNUINCLUDES)
LDFLAGS      += -g $(ROOTLDFLAGS) 


LIBS          = $(ROOTLIBS)  $(SYSLIBS) 
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

ROOT_LIBRARY = libOscillation.so
LIB_OBJS = MatrixDecomp/zheevc3.o MatrixDecomp/zheevh3.o MatrixDecomp/zheevq3.o MatrixDecomp/zhetrd3.o AtNuOscillate.o PMNS.o PMNS_Fast.o ProductionHeight.o OscCalc.o oscillationDict.o
CLASS_HEADERS = MatrixDecomp/zheevc3.h MatrixDecomp/zheevh3.h MatrixDecomp/zheevq3.h MatrixDecomp/zhetrd3.h AtNuOscillate.h PMNS.h PMNS_Fast.h ProductionHeight.h OscCalc.h


all : ${ROOT_LIBRARY}


#The library
$(ROOT_LIBRARY) : $(LIB_OBJS) 
	@echo "Linking $@ ..."
ifeq ($(PLATFORM),macosx)
# We need to make both the .dylib and the .so
	$(LD) $(SOFLAGS)$@ $(LDFLAGS) $^ $(OutPutOpt) $@
ifneq ($(subst $(MACOSX_MINOR),,1234),1234)
ifeq ($(MACOSX_MINOR),4)
	ln -sf $@ $(subst .$(DllSuf),.so,$@)
else
	$(LD) -bundle -undefined $(UNDEFOPT) $(LDFLAGS) $^ \
		$(OutPutOpt) $(subst .$(DllSuf),.so,$@)
endif
endif
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $(LIBS) $(LIB_OBJS) -o $@
endif



%.$(OBJSUF) : %.$(SRCSUF)
	@echo "<**Compiling**> "$<
	$(CXX) $(CXXFLAGS) -c $< -o  $@

%.$(OBJSUF) : %.C
	@echo "<**Compiling**> "$<
	$(CXX) $(CXXFLAGS) $ -c $< -o  $@


oscillationDict.C: $(CLASS_HEADERS)
	@echo "Generating dictionary ..."
	@ rm -f *Dict* 
	rootcint  $@  -c $(CXXFLAGS) $(CLASS_HEADERS) LinkDef.h


clean:
	@rm -f *Dict*
	@rm -f ${LIB_OBJS}
	@rm -f $(subst .$(DLLSUF),.so,$(ROOT_LIBRARY))	
	@rm -f ${PROGRAMS}

install: $(ROOT_LIBRARY)
	install -d $(CCPLUSNC_INC_DIR)
	install -d $(CCPLUSNC_LIB_DIR)
ifeq ($(PLATFORM),macosx)
	@install -c -m 755 $(ROOT_LIBRARY) $(subst .$(DllSuf),.so,$(ROOT_LIBRARY)) $(CCPLUSNC_LIB_DIR)
else
	install -c -m 755 $(ROOT_LIBRARY) $(CCPLUSNC_LIB_DIR)
endif
	install -c -m 644 $(CLASS_HEADERS) $(CCPLUSNC_INC_DIR)


#############################################################################



