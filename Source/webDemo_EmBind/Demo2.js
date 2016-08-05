document.write("3d DistPtPt Demo begin" +'\n' + "<br>" + "<br>");

var vcs = new Module.VCSSystem();

var pt1 = new Module.VCSMPoint3d(1, 0, 0);
var pt2 = new Module.VCSMPoint3d(2, 0, 0);
var cor = new Module.VCSMPoint3d(0, 0, 0);

var t = new Module.VCSMMatrix3d();

var b1 = vcs.createRBody(1, t, cor);
var b2 = vcs.createRBody(2, t, cor);

document.write("before solve pt1.x = " + pt1.x +'\n' + "<br>");
document.write("before solve pt1.y = " + pt1.y +'\n' + "<br>");
document.write("before solve pt1.z = " + pt1.z +'\n' + "<br>");
document.write("before solve pt2.x = " + pt2.x +'\n' + "<br>");
document.write("before solve pt2.y = " + pt2.y +'\n' + "<br>");
document.write("before solve pt2.z = " + pt2.z +'\n' + "<br>" + "<br>");

var h = vcs.create3dDistPtPt(b1, b2, pt1, pt2, null, null, 10, Module.VCSConEqMode.kVCSEQ, null);

var status = vcs.solve(Module.VCSSolveMode.kNormal, true);
var status_str = Module.getVCSStatus(status);

document.write("solve status = " + status_str +'\n' + "<br>" + "<br>");

var pt1AfterSolve = Module.getVCSMPoint3dAfterSolve(pt1, b1);
var pt2AfterSolve = Module.getVCSMPoint3dAfterSolve(pt2, b2);

document.write("after solve pt1.x = " + pt1AfterSolve.x +'\n' + "<br>");
document.write("after solve pt1.y = " + pt1AfterSolve.y +'\n' + "<br>");
document.write("after solve pt1.z = " + pt1AfterSolve.z +'\n' + "<br>");
document.write("after solve pt2.x = " + pt2AfterSolve.x +'\n' + "<br>");
document.write("after solve pt2.y = " + pt2AfterSolve.y +'\n' + "<br>");
document.write("after solve pt2.z = " + pt2AfterSolve.z +'\n' + "<br>" + "<br>");

pt1.delete();
pt2.delete();
cor.delete();
t.delete();
b1.delete();
b2.delete();
//h.delete();

//vcs.delete();

document.write("3d DistPtPt Demo end" +'\n' + "<br>" + "<br>");
