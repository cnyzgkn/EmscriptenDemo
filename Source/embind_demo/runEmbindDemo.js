var status = Module.solve();
//var status_str = Module.getVCSStatus(status);
//document.write("solve status = " + status_str +'\n' + "<br>" + "<br>");
document.write((status == Module.VCSStatus.kNull) + "<br>");
document.write((status == Module.VCSStatus.kSolved) + "<br>");
