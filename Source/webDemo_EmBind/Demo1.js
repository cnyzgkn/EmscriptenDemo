document.write("3d DistPtLn Demo begin" +'\n' + "<br>" + "<br>");

var vcs = new Module.VCSSystem();

var pt = new Module.VCSMPoint3d(5, 5, 0);
var ln = new Module.VCSMLine3d(new Module.VCSMPoint3d(0, 2, 0), new Module.VCSMPoint3d(1, 2, 0));

var cor = new Module.VCSMPoint3d(0, 0, 0);
var t = new Module.VCSMMatrix3d();

var ptbody = vcs.createRBody(1, t, cor);
var lnbody = vcs.createRBody(2, t, cor);

var ptOnLn = ln.mOrigin;
var dircOfLn = ln.mDirection;

document.write("before solve ptOnLn.x = " + ptOnLn.x +'\n' + "<br>");
document.write("before solve ptOnLn.y = " + ptOnLn.y +'\n' + "<br>");
document.write("before solve ptOnLn.z = " + ptOnLn.z +'\n' + "<br>");
document.write("before solve dircOfLn.x = " + dircOfLn.x +'\n' + "<br>");
document.write("before solve dircOfLn.y = " + dircOfLn.y +'\n' + "<br>");
document.write("before solve dircOfLn.z = " + dircOfLn.z +'\n' + "<br>" + "<br>");

var biasPt = new Module.VCSMPoint3d(0, 0, 0);
var h = vcs.create3dDistPtLn(false, biasPt, ptbody, lnbody, pt, ln, null, null, 6, Module.VCSConEqMode.kVCSEQ, null);

var status = vcs.solve(Module.VCSSolveMode.kNormal, true);
var status_str = Module.getVCSStatus(status);

document.write("solve status = " + status_str +'\n' + "<br>" + "<br>");

var ptAfterSolve = Module.getVCSMPoint3dAfterSolve(pt, ptbody);
var lnAfterSolve = Module.getVCSMLine3dAfterSolve(ln, lnbody);

var ptOnLnAfterSolve = ln.mOrigin;
var dircOfLnAfterSolve = ln.mDirection;

document.write("after solve ptOnLnAfterSolve.x = " + ptOnLnAfterSolve.x +'\n' + "<br>");
document.write("after solve ptOnLnAfterSolve.y = " + ptOnLnAfterSolve.y +'\n' + "<br>");
document.write("after solve ptOnLnAfterSolve.z = " + ptOnLnAfterSolve.z +'\n' + "<br>");
document.write("after solve dircOfLnAfterSolve.x = " + dircOfLnAfterSolve.x +'\n' + "<br>");
document.write("after solve dircOfLnAfterSolve.y = " + dircOfLnAfterSolve.y +'\n' + "<br>");
document.write("after solve dircOfLnAfterSolve.z = " + dircOfLnAfterSolve.z +'\n' + "<br>" + "<br>");

pt.delete();
ln.delete();
cor.delete();
t.delete();
ptbody.delete();
lnbody.delete();
ptOnLn.delete();
dircOfLn.delete();
biasPt.delete();
//h.delete();

//vcs.delete();

document.write("3d DistPtLn Demo end" +'\n' + "<br>" + "<br>");