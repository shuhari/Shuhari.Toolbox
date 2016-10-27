# Shuhari's Toolbox

Misc uttility applications written using Qt. Includes:

## uttilities category

### Hub
Entry point for all utility programs

### Clean directory
Delete unused file (such as thumbs.db) and empty directories

### Encode/Decode
Encode and decode test for Base64/MD5/Url/HTML


## Build pre-requirement
NOTE: This project is tested on Win7/Win10. It should also run on Win 8/8.1, but with no grarantee.

Tools required:
* TDM-GCC (64bit)
* Qt 5.6 (or higher) compiled with TDM-GCC


## Build step
1. Ensure you are in the cloned git repository
2. Run __build.cmd rebuild [debug | release]__
   Rebuild the project
3. Run __build.cmd lrelease__ to generate translation files

If all runs ok, you should see executable and accessory files in the _build/[debug | release]_ directory.
