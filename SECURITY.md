# Security Policy
## Supported Versions
Take this software as "rolling release". There won't be any two concurrent versions of this tool.  
**Only the latest version is supported.**

## Reporting a Vulnerability
It's a command-line tool running in user mode that just reads a file's first few bytes, matches them against known file signatures and then properly renames the file, everything while calling only C Standard Library functions.  
I don't expect any vulnerabilities that allows any form of exploitation or that "steals your credentials" or whatever.

But if there actually is a serious vulnerability due to Computer Science Magic™️, feel free to open a  GitHub Issue or Security Advisory!
