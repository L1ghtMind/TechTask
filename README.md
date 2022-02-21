# TechTask

data.zgml file is located in [Project Folder/TechTask] where all .cpp files are located.

#If you get an error "error MSB8020: Build Tools v142 not found":
Make sure that Build Tools v142 is installed in the project: go to Project->Properties->General->Platform Toolset.
If not - you can change the version in the drop-down menu (default v142 for vs 2019, v143 for vs 2022) and it will rebuild the project.
Or install the desired version through the visual studio installer in the individual components tab.
