APPNAME = magicfix
OUTDIR = build
INSTALLDIR = /usr/local/bin

compile:
	@cmake -DCMAKE_BUILD_TYPE=Release -B$(OUTDIR) -S.
	@cmake --build $(OUTDIR) --config Release

debug:
	@cmake -DCMAKE_BUILD_TYPE=Debug -B$(OUTDIR) -S.
	@cmake --build $(OUTDIR) --config Debug

install:
	@install -m755 $(OUTDIR)/$(APPNAME) $(INSTALLDIR)/$(APPNAME)

uninstall:
	@rm $(INSTALLDIR)/$(APPNAME)

clean:
	@rm -r $(OUTDIR)
