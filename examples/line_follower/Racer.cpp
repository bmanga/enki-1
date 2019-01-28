/*
    Enki - a fast 2D robot simulator
    Copyright (C) 2017 Bernd Porr
    Copyright (C) 1999-2016 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006-2008 Laboratory of Robotics Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication 
    arising from research using this software are asked to add the 
    following reference:
    Enki - a fast 2D robot simulator
    http://home.gna.org/enki
    Stephane Magnenat <stephane at magnenat dot net>,
    Markus Waibel <markus dot waibel at epfl dot ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "Racer.h"

namespace Enki
{
	Racer::Racer() :
		DifferentialWheeled(5.2, 100, 0.05),
        infraredSensor0(this, Vector(10, 7),  1.8, M_PI/2, 10, 1200, -0.9, 7, 20),
        infraredSensor1(this, Vector(10, 5),  1.8, M_PI/4, 10, 1200, -0.9, 7, 20),
        infraredSensor2(this, Vector(10, 3),  1.8, 0,      10, 1200, -0.9, 7, 20),
        infraredSensor3(this, Vector(10, -3), 1.8, 0,      10, 1200, -0.9, 7, 20),
        infraredSensor4(this, Vector(10, -5), 1.8, -M_PI/4,10, 1200, -0.9, 7, 20),
        infraredSensor5(this, Vector(10, -7), 1.8, -M_PI/2,10, 1200, -0.9, 7, 20),
        infraredSensor6(this, Vector(-10, -5),1.8, -M_PI,  10, 1200, -0.9, 7, 20),
        infraredSensor7(this, Vector(-10, 5), 1.8, -M_PI,  10, 1200, -0.9, 7, 20),
		camera(this, Vector(0, 0), 0, 0.0, M_PI/4, 50),
        groundSensorLeft (this, Vector(10, 5), 0, 1, 1, 0),
        groundSensorRight(this, Vector(10, -5),0, 1, 1, 0),


        groundSensorFrontP1(this, Vector(15, 5), 0, 1, 1, 0), //left 1
        groundSensorFrontP2(this, Vector(20, 3.5),0, 1, 1, 0), //left 2
        groundSensorFrontP3(this, Vector(20, 0), 0, 1, 1, 0), //center
        groundSensorFrontP4(this, Vector(20, -3.5),0, 1, 1, 0), //right 2
        groundSensorFrontP5(this, Vector(15, -5), 0, 1, 1, 0), //right 1

//        groundSensorFrontP1(this, Vector(15, 6), 0, 1, 1, 0), //left 1
//        groundSensorFrontP2(this, Vector(20, 4),0, 1, 1, 0), //left 2
//        groundSensorFrontP3(this, Vector(20, 0), 0, 1, 1, 0), //center
//        groundSensorFrontP4(this, Vector(20, -2.5),0, 1, 1, 0), //right 2
//        groundSensorFrontP5(this, Vector(15, -6), 0, 1, 1, 0), //right 1

        groundSensorBackP1(this, Vector(13, 5),0, 1, 1, 0),
        groundSensorBackP2(this, Vector(20, 4.5), 0, 1, 1, 0),
        groundSensorBackP3(this, Vector(20, 0),0, 1, 1, 0),
        groundSensorBackP4(this, Vector(20, -3), 0, 1, 1, 0),
        groundSensorBackP5(this, Vector(13, -5),0, 1, 1, 0)

	{

        addLocalInteraction(&infraredSensor0);
        addLocalInteraction(&infraredSensor1);
        addLocalInteraction(&infraredSensor2);
        addLocalInteraction(&infraredSensor3);
        addLocalInteraction(&infraredSensor4);
        addLocalInteraction(&infraredSensor5);
        addLocalInteraction(&infraredSensor6);
        addLocalInteraction(&infraredSensor7);
		addLocalInteraction(&camera);
		addLocalInteraction(&groundSensorLeft);
		addLocalInteraction(&groundSensorRight);

        addLocalInteraction(&groundSensorFrontP1);
        addLocalInteraction(&groundSensorFrontP2);
        addLocalInteraction(&groundSensorFrontP3);
        addLocalInteraction(&groundSensorFrontP4);
        addLocalInteraction(&groundSensorFrontP5);

        addLocalInteraction(&groundSensorBackP1);
        addLocalInteraction(&groundSensorBackP2);
        addLocalInteraction(&groundSensorBackP3);
        addLocalInteraction(&groundSensorBackP4);
        addLocalInteraction(&groundSensorBackP5);
		
        setRectangular(20,10,5, 80); // length, width, height, mass of the robot
        setColor(0);

    }


}
