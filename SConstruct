import os
import os.path as path
import platform

#------------------------set additional build options--------------------------
AddOption("--static",dest="static",action="store_true",
          default=False,help="create statically linked code")

#----------------add additional build variables--------------------------------
var = Variables()
var.Add("CXX","set the compiler to use","g++")
var.Add(PathVariable("BOOSTLIBDIR","BOOST library installation directory","/usr/lib"))
var.Add(PathVariable("BOOSTINCDIR","BOOST header installation directory","/usr/include"))


#---------------create the build environment-----------------------------------
env = Environment(variables=var)
#for the moment we relie on pkg-config for libpniutils
env["ENV"]["PKG_CONFIG_PATH"] = os.environ["PKG_CONFIG_PATH"]
env.ParseConfig('pkg-config --libs --cflags pniutils')
env.Replace(CXX = env["CXX"])

#set some default compiler options
env.Append(CXXFLAGS=["-std=c++0x"])
env.Append(CXXFLAGS=["-Wall","-g","-O2"])

env.AppendUnique(CPPPATH=[env["BOOSTINCDIR"]])
env.AppendUnique(LIBPATH=[env["BOOSTLIBDIR"]])

#------------------start with configuration------------------------------------
conf = Configure(env);

if not conf.CheckLib("boost_program_options"):
    print "BOOST program_options library not installed!"
    Exit(1)

env = conf.Finish()

if GetOption("static"):
    env.Append(LIBS = ["pthread"])



program_env = env.Clone()
Export("program_env")


#start the SConscript files for the individual tools
SConscript("src/mcaops/SConscript")
