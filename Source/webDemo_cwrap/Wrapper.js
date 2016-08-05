var createVCSSystem = Module.cwrap('Wrapper_createVCSSystem', 'number', []);
var createVCSMPoint3d = Module.cwrap('Wrapper_createVCSMPoint3d', 'number', ['number', 'number', 'number']);
var createVCSMMatrix3d = Module.cwrap('Wrapper_createVCSMMatrix3d', 'number', []);
var showPointX = Module.cwrap('Wrapper_showPointX', 'number', ['number', 'number']);
var showPointY = Module.cwrap('Wrapper_showPointY', 'number', ['number', 'number']);
var createRBody = Module.cwrap('Wrapper_createRBody', 'number', ['number', 'number', 'number', 'number']);
var create3dDistPtPt = Module.cwrap('Wrapper_create3dDistPtPt', '', ['number', 'number', 'number', 'number', 'number', 'number']);
var showVCSStatus = Module.cwrap('Wrapper_showVCSStatus', 'string', ['number']);
var solve = Module.cwrap('Wrapper_solve', 'number', ['number']);