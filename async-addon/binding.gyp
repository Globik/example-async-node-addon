{
"targets":[
{
"target_name":"asyncAddon",
"sources":["async-addon.cc"],
"conditions": [
              ["OS=='win'",{
              "include_dirs": [
	                            "C:/Program Files/Windows Kits/8.0/Include/um",
	                            "C:/Program Files/Windows Kits/8.0/Include/shared",
	                            "C:/Program Files/Windows Kits/10/Include/10.0.10150.0/ucrt"
                                ],
	   "libraries":[
	                # beer in mind, pathes to the needed headers and libraries can be different from platform to platform
	                #"C:/Program Files/Windows Kits/10/Lib/10.0.10150.0/ucrt/x86/ucrt.lib",
	                "C:/Program Files/Windows Kits/10/Lib/10.0.10150.0/ucrt/x86/libucrt.lib"
	               ],
	   "defines":[
	              "WIN32",
	              #"_MSC_VER=1900",
	              #"NOMINMAX",
	              "DELAYIMP_INSECURE_WRITABLE_HOOKS"
	              ]
	   }
	   ],
	   ["OS=='linux'", {
         # do stuff by default
		 }]
	   ]
}
]	   
}