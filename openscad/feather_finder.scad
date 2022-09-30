//https://github.com/mrWheel/YAPP_Box
box_height=7.2;
depth=50;
battery_size=[37,25.5,5.2];
featherboard_size=[50.8,22.8,7.2];
bno055_size=[20.32,25.04,7.2];
cable_length=40;

include <BOSL2/std.scad>
include <BOSL2/joiners.scad>
include<YAPPgenerator_v15.scad>


//-- which part do you want to print?
printBaseShell      = true;
printLidShell       = true;
printHolder         = true;

color("gray")
translate([pcbX,pcbY+battery_size.y+standoffDiameter+2.54/2+1.5 , basePlaneThickness+standoffHeight])
import("ESP32FeatherV2.stl", convexity=3);


//battery
//#color("gray")
//translate([pcbX,pcbY,pcbZ])
//cube(battery_size);


bno_position=[pcbX+featherboard_size.x/2,pcbY+battery_size.y+standoffDiameter+2.54+ cable_length+ featherboard_size.y+standoffDiameter-1.5 , basePlaneThickness+standoffHeight];
color("gray")
translate(bno_position)
rotate([0,0,90])
import("bno055.stl", convexity=3);

difference() {
YAPPgenerate();
//vixen finder dovetail
//https://github.com/revarbat/BOSL2/wiki/joiners.scad#module-dovetail
translate([pcbX+featherboard_size.x/2,40,0])
cube([18.5,39,4], center=true);
//
}

//holder
holder_margin=0.4;
if(printHolder)
translate([90,110,39.4/2])
rotate([90,0,0])
translate([0,0,9])
difference() {
    union() {
    translate([0,-(39-4.2-holder_margin)/2 ,0])   
    cube([10,4.2,28], center=true);
    dovetail("female", width=32, height=9, slide=39-holder_margin, angle=30);
    translate([0,0,49])
    cube([18.5-holder_margin,39-holder_margin,100], center=true);
    }

    for (i = [15, 45, 75]){
        translate([0, 0, i])
        rotate([0,90,0])
        cylinder(  30, d=25, center=true, $fn=360);
    }
}

