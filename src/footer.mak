

.PHONY: init 

init: makedirs

makedirs: $(OUTDIR)

.PHONY: $(OUTDIR)

# copy structure of the src directory in the output directory
$(OUTDIR): $(SRCDIR)
	mkdir -p $(OUTDIR)


# every binary shall depend on the init target
CMNDEPS += init



distclean:: 
	rm -rf $(BASEDIR)/Debug $(BASEDIR)/Release




%.o : %.cpp
	$(CC) -c $(CFLAGS) -o $@ $< 







clean::
	rm -f $(DEPEND) 

DEPEND=.depend
DEPENDTMP=.depend.tmp

depend: $(DEPEND)

.PHONY: $(DEPEND)

ifneq ($(RECURSIVE),1) 
export RECURSIVE=1
$(DEPEND): $(SRCS) $(HDRS)
	@echo -n "checking dependencies .. "
	@rm -f $(DEPENDTMP)
	@for s in $(SRCS) ; do \
		$(CC) -MM -MG $$s >> $(DEPENDTMP) ; \
		echo $$s: $(CMNDEPS) >> $(DEPENDTMP) ; \
	done
	@if ! [ -e  $(DEPEND) ] || ! diff -q $(DEPENDTMP) $(DEPEND) ; then \
		mv $(DEPENDTMP) $(DEPEND) ; \
		echo "modified: recursive build" ; \
		$(MAKE) $(MAKECMDGOALS) ; \
		exit 0 ; \
	else \
		touch $(DEPEND) ; \
		echo "unmodified" ; \
	fi

else
$(DEPEND):
endif
-include $(DEPEND)
