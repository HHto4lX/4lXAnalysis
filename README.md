ZZAnalysis
==========

To install a complete CMSSW 8X area (including this package)
------------------------------
2016 data analysis

Please use CMSSW_8_0_29. 

Download and execute the setup script:
```
wget -O ${TMPDIR}/checkout_80X.csh https://raw.githubusercontent.com/CJLST/ZZAnalysis/miniAOD_80X/checkout_80X.csh
cd $CMSSW_BASE/src
cmsenv
chmod u+x ${TMPDIR}/checkout_80X.csh
${TMPDIR}/checkout_80X.csh
```

To install a complete CMSSW 9X area (including this package)
------------------------------
2017 data analysis

Please use CMSSW_9_4_9.

Download and execute the setup script:
```
wget -O ${TMPDIR}/checkout_9X.csh https://raw.githubusercontent.com/CJLST/ZZAnalysis/miniAOD_80X/checkout_9X.csh
cd $CMSSW_BASE/src
cmsenv
chmod u+x ${TMPDIR}/checkout_9X.csh
${TMPDIR}/checkout_9X.csh
```

To install a complete CMSSW 10X area (including this package)
------------------------------
2018 data analysis

Please use CMSSW_10_2_5_patch1. 

Download and execute the setup script:
```
wget -O ${TMPDIR}/checkout_10X.csh https://raw.githubusercontent.com/CJLST/ZZAnalysis/miniAOD_80X/checkout_10X.csh
cd $CMSSW_BASE/src
cmsenv
chmod u+x ${TMPDIR}/checkout_10X.csh
${TMPDIR}/checkout_10X.csh
```

To update this package from the release
------------------------------------------
In the package directory, simply issue
```
git pull
```

To commit and push new changes
------------------------------
To commit directly (you need write access to the repository):
```
git pull
[edit files]
```
Once you are ready to commit
```
git pull
git add [files to be added]
git commit -m ["commit message"] [files to be added]
git push origin miniAOD_80X
```

Otherwise you can make a fork of the repository, develop therein, and make a pull request in the same way as for CMSSW.

Code documentation
------------------
Please see the [gitHub wiki](https://github.com/CJLST/ZZAnalysis) for more documentation.
