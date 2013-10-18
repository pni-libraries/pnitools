.\" detinfo
.\" Contact Eugen Wintersberger <eugen.wintersberger@desy.de> for typos and corrections
.TH nxcat 1 "Jun 17,2013" "" "User commands"
.SH NAME
nxcat - output scalar data from a Nexus file

.SH SYNOPSIS
.B nxcat [OPTIONS] SOURCE [SOURCE ...]

.SH DESCRIPTION
\fBnxcat\fR prints the output of one or more fields stored in Nexus files to
standard out. The fields are specified by Nexus paths. For more information
about Nexus path notation have a look at

.SH OPTIONS
The programm takes the following options:
.TP
\fB\-h\fR,\fB\-\-help\fR
print short program help
.TP
\fB\-\-header\fR
Print header with column name and unit information to the output.
.TP
\fB\-s\fR,\fB\-\-start\fR
first index
.TP
\fB\-e\fR,\fB\-\-end\fR
last index

.SH EXIT CODE
0 in the case of success, 1 otherwise

.SH AUTHOR
Written bei Eugen Wintersberger <eugen.wintersberger@desy.de>

.SH COPYRIGHT
Copyright 2013 Eugen Wintersberger License GLPLv2+: GNU GPL version 2 or later
<http://gnu.org/license/gpl.html>.  This is free software: you are free to
change and redistribute it. There is no WARRENTY, to the extent permitted by
law.

.SH SEE ALSO
.IP \fBpni-tools\fR 



