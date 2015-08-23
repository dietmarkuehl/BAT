#  Makefile                                                      -*-makefile-*-
#  ----------------------------------------------------------------------------

NAME     = bat
COMPILER = gcc

CXX      = /opt/llvm/bin/clang++
BINDIR   = bin/$(COMPILER)
CPPFLAGS = -I. -I/usr/local/include/bsl
CXXFLAGS = -W -Wall -g
DEPFLAGS = -M
LDFLAGS  = -L$(BINDIR)
LDLIBS   = -l$(NAME) -lbsl

#  ----------------------------------------------------------------------------

LIBCXXFILES += \
	bat/gen/equalto.cpp \
	bat/gen/lessthan.cpp \
	bat/ma/allocator.cpp \
	bat/mf/isbaseof.cpp \

LIBOFILES    = $(LIBCXXFILES:%.cpp=$(BINDIR)/%.o)
TESTCXXFILES = $(LIBCXXFILES:%.cpp=%.t.cpp)

CXXFILES = $(LIBCXXFILES) $(TESTCXXFILES)

.PHONY: default
default: check

.PHONY: lib
lib: $(BINDIR)/lib$(NAME).a

.PHONY: check
check: $(TESTCXXFILES:%.cpp=$(BINDIR)/%)
	@for f in $(TESTCXXFILES:%.cpp=%); \
	do \
	    echo running $(BINDIR)/$$f; \
	    $(BINDIR)/$$f --force-colour; \
	done

#  ----------------------------------------------------------------------------

$(BINDIR)/lib$(NAME).a: $(LIBOFILES)
	$(AR) rcu $@ $(LIBOFILES)

$(BINDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -o $@ $(CPPFLAGS) $(CXXFLAGS) -c $(@:$(BINDIR)/%.o=%.cpp)

$(BINDIR)/%.t: $(BINDIR)/%.t.o lib
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
