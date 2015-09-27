#  Makefile                                                      -*-makefile-*-
#  ----------------------------------------------------------------------------

NAME     = bat

COMPILER = default
CXXFLAGS = -W -Wall -g
DEPFLAGS = -M

ifeq ($(COMPILER),gcc)
	CXX      = /opt/gcc-current/bin/g++
	CXXFLAGS = -W -Wall -g
	DEPFLAGS = -M
endif
ifeq ($(COMPILER),clang)
	CXX      = /opt/llvm-current/bin/clang++
	CXXFLAGS = -W -Wall -g
	DEPFLAGS = -M
endif

BINDIR   = bin/$(COMPILER)
CPPFLAGS = -I. -I/usr/local/include/bsl
LDFLAGS  = -L$(BINDIR)
LDLIBS   = -l$(NAME) -lbsl
RANLIB   = ranlib

#  ----------------------------------------------------------------------------

LIBCXXFILES += \
	bat/gen/equalto.cpp \
	bat/gen/lessthan.cpp \
	bat/gen/tuple.cpp \
	bat/gen/tupleequalto.cpp \
	bat/gen/tuplelessthan.cpp \
	bat/gen/tupleoutput.cpp \
	bat/gen/tuplevalue.cpp \
	bat/ma/allocator.cpp \
	bat/mf/isbaseof.cpp \

# LIBCXXFILES = bat/gen/tupleoutput.cpp

LIBOFILES    = $(LIBCXXFILES:%.cpp=$(BINDIR)/%.o)
TESTCXXFILES = $(LIBCXXFILES:%.cpp=%.ut.cpp)

CXXFILES = $(LIBCXXFILES) $(TESTCXXFILES)

.PHONY: default
default: check

.PHONY: lib
lib: $(BINDIR)/lib$(NAME).a

.PHONY: check
check: $(TESTCXXFILES:%.cpp=$(BINDIR)/%.o) $(TESTCXXFILES:%.cpp=$(BINDIR)/%)
	@for f in $(TESTCXXFILES:%.cpp=%); \
	do \
	    echo running $(BINDIR)/$$f; \
	    $(BINDIR)/$$f --force-colour; \
	done

#  ----------------------------------------------------------------------------

$(BINDIR)/lib$(NAME).a: $(LIBOFILES)
	$(AR) rcu $@ $(LIBOFILES)
	$(RANLIB) $@

$(BINDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -o $@ $(CPPFLAGS) $(CXXFLAGS) -c $(@:$(BINDIR)/%.o=%.cpp)

$(BINDIR)/%.ut: $(BINDIR)/%.ut.o lib
	@mkdir -p $(@D)
	$(CXX) -o $@ $(LDFLAGS) $(@:%=%.o) $(LDLIBS)

#  ----------------------------------------------------------------------------

.PHONY: depend
depend $(BINDIR)/make.depend:
	@mkdir -p $(BINDIR)
	@cat /dev/null > $(BINDIR)/make.depend
	for f in $(CXXFILES:%.cpp=%); \
	do \
		$(CXX) $(DEPFLAGS) $(CPPFLAGS) $$f.cpp -MT $(BINDIR)/$$f.o >> $(BINDIR)/make.depend; \
	done

.PHONY: clean
clean:
	$(RM) -r $(BINDIR)


include $(BINDIR)/make.depend
