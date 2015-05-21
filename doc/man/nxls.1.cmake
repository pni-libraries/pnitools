.\" detinfo
.\" Contact Eugen Wintersberger <eugen.wintersberger@desy.de> for typos and corrections
.TH xml2nx 1 "Jul 22,2013" "" "User commands"
.SH NAME
nxls - list content of a Nexus file

.SH SYNOPSIS
.B nxls [OPTIONS] NEXUSPATH 

.SH DESCRIPTION
\fBnxls\fR lists the content of a Nexus file. Like its Unix counter part
\fBls\fR, \fBnxls\fR shows the content of the file relative to a particular
group within the file. In the simplest case this is the root group of the file. 
As the command line argument must be a valid Nexus path in no case the name of
the file alone will suffice. It is at least necessary to add the root part. 
In such a case a possible call of \fBnxls\fR would look like this
.P
.RS 2
$ nxls data.nxs://
.RE
.P
By default \fBnxls\fR removes the leading part of the path of the individual 
Nexus objects. This is just to save space in the output. To obtain the full 
path use the \fB\-f\fR option.

.SH OPTIONS
The programm takes the following options:
.TP
\fB\-h\fR,\fB\-\-help\fR
print short program help
.TP
\fB\-r\fR,\fB\-\-recursive\fR
show the content of all subgroups of a given Nexus group
.TP
\fB\-a\fR,\fB\-\-show\-attributes\fR
shows attributes in addition to groups and field.
.TP
\fB-f\fR, \fB\-\-full\-path\fR
show the full path for each object
.TP
\fB-l\fR, \fB\-\-long\fR
show additional information for each object

.SH Examples
.TP
nxls data.nxs://
shows the content of the root group
.TP
nxls -f data.nxs://:NXentry/:NXinstrument
lists all objects in the instrument group of the Nexus file with full path
.TP
nxls -a data.nxs://:NXentry/:NXinstrument
lists all objects in the instrument group of the Nexus file including all 
attributes
.TP
nxls -al data.nxs://:NXentry/:NXinstrument/:NXdetector/data
shows detailed information about the data field in the detector group

.SH EXIT CODE
0 in the case of success, 1 otherwise

.SH AUTHOR
Written bei Eugen Wintersberger <eugen.wintersberger@desy.de>

.SH COPYRIGHT
Copyright 2013 Eugen Wintersberger License GLPLv2+: GNU GPL version 2 or later
.br
<http://gnu.org/license/gpl.html>.  This is free software: you are free to
.br
change and redistribute it. There is no WARRENTY, to the extent permitted by
.br
law.

.SH SEE ALSO
For more information consult the info page for the \fBpni-tools\fR program 
suite \fBinfo pni-tools\fR.



