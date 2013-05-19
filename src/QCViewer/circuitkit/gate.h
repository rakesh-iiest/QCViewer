/*--------------------------------------------------------------------
QCViewer
Copyright (C) 2011 Alex Parent and The University of Waterloo,
Institute for Quantum Computing, Quantum Circuits Group

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

See also 'ADDITIONAL TERMS' at the end of the included LICENSE file.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

QCViewer is a trademark of the of the The University of Waterloo,
Institute for Quantum Computing, Quantum Circuits Group

Authors: Alex Parent, Jacob Parker, Marc Burns
---------------------------------------------------------------------*/


#ifndef GATE
#define GATE

#include <string>
#include <memory>
#include <vector>

//used to specify a control number and polarity
class Control
{
public:
    Control (int,bool);
    unsigned int wire;
    bool polarity;
};

/*
GATE
---------------
This is the general gate class from which all gates are derived.
Name is kept private since in the case of gates like the arbitray
rotation gate we may want the name to be dependent on the rot amount
*/

class Gate
{
public:
    virtual ~Gate();
    Gate();
    virtual std::shared_ptr<Gate> clone() const=0;
    virtual std::string getName() const=0;

    virtual unsigned int getNumGates() const;
    std::vector <Control> controls;
    std::vector <unsigned int> targets;
    bool ctrls;
};

struct GateAttributes {
  GateAttributes();
  int loop_count;
};

//A gate matrix struct for UGate
struct gateMatrix {
    ~gateMatrix();
    gateMatrix(int);
    gateMatrix();
    unsigned int dim;
    std::complex<float_type> * data;
};

//A general unitary gate
class UGate : public Gate
{
public:
    UGate(std::string);
    UGate(std::string,std::string);
    std::shared_ptr<Gate> clone() const;
    std::string getName() const;
    void setName(std::string);
private:
    std::string name;
};

//An arbitrary rotation gate
class RGate : public Gate
{
public:
    enum Axis { X, Y, Z };
    RGate(float_type, Axis);
    RGate(Axis,int,int);
    std::shared_ptr<Gate> clone() const;
    std::string getName() const;
    float_type get_rotVal () const; // XXX: remove float_type, consildate this stuff!!
    void set_rotVal (float_type);
    Axis get_axis () const;
    void set_axis (Axis);
    bool frac;
    int numer,denom;
private:
    float_type rot;
    Axis axis;
};

#endif
