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
	@cp $(OUTDIR)/$(APPNAME) $(INSTALLDIR)/$(APPNAME)

clean:
	@rm -r $(OUTDIR)