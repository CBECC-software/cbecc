/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_OS_SOLARCOLLECTORPERFORMANCE_FLATPLATE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SOLARCOLLECTORPERFORMANCE_FLATPLATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SolarCollectorPerformance_FlatPlateFields
 *  \brief Enumeration of OS:SolarCollectorPerformance:FlatPlate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SolarCollectorPerformance_FlatPlateFields, )
#else
class OS_SolarCollectorPerformance_FlatPlateFields: public ::EnumBase<OS_SolarCollectorPerformance_FlatPlateFields> {
 public: 
  enum domain 
  {
Handle, Name, GrossArea, TestFluid, TestFlowRate, TestCorrelationType, Coefficient1ofEfficiencyEquation, Coefficient2ofEfficiencyEquation, Coefficient3ofEfficiencyEquation, Coefficient2ofIncidentAngleModifier, Coefficient3ofIncidentAngleModifier,   };
  OS_SolarCollectorPerformance_FlatPlateFields()
   : EnumBase<OS_SolarCollectorPerformance_FlatPlateFields>(Handle) {} 
  OS_SolarCollectorPerformance_FlatPlateFields(const std::string &t_name) 
   : EnumBase<OS_SolarCollectorPerformance_FlatPlateFields>(t_name) {} 
  OS_SolarCollectorPerformance_FlatPlateFields(int t_value) 
   : EnumBase<OS_SolarCollectorPerformance_FlatPlateFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SolarCollectorPerformance_FlatPlateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SolarCollectorPerformance_FlatPlateFields>::value()); }
   private:
    friend class EnumBase<OS_SolarCollectorPerformance_FlatPlateFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_SolarCollectorPerformance_FlatPlateFields::Handle, "Handle", "Handle"},
{ OS_SolarCollectorPerformance_FlatPlateFields::Name, "Name", "Name"},
{ OS_SolarCollectorPerformance_FlatPlateFields::GrossArea, "GrossArea", "Gross Area"},
{ OS_SolarCollectorPerformance_FlatPlateFields::TestFluid, "TestFluid", "Test Fluid"},
{ OS_SolarCollectorPerformance_FlatPlateFields::TestFlowRate, "TestFlowRate", "Test Flow Rate"},
{ OS_SolarCollectorPerformance_FlatPlateFields::TestCorrelationType, "TestCorrelationType", "Test Correlation Type"},
{ OS_SolarCollectorPerformance_FlatPlateFields::Coefficient1ofEfficiencyEquation, "Coefficient1ofEfficiencyEquation", "Coefficient 1 of Efficiency Equation"},
{ OS_SolarCollectorPerformance_FlatPlateFields::Coefficient2ofEfficiencyEquation, "Coefficient2ofEfficiencyEquation", "Coefficient 2 of Efficiency Equation"},
{ OS_SolarCollectorPerformance_FlatPlateFields::Coefficient3ofEfficiencyEquation, "Coefficient3ofEfficiencyEquation", "Coefficient 3 of Efficiency Equation"},
{ OS_SolarCollectorPerformance_FlatPlateFields::Coefficient2ofIncidentAngleModifier, "Coefficient2ofIncidentAngleModifier", "Coefficient 2 of Incident Angle Modifier"},
{ OS_SolarCollectorPerformance_FlatPlateFields::Coefficient3ofIncidentAngleModifier, "Coefficient3ofIncidentAngleModifier", "Coefficient 3 of Incident Angle Modifier"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_SolarCollectorPerformance_FlatPlateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SolarCollectorPerformance_FlatPlateFields> OptionalOS_SolarCollectorPerformance_FlatPlateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SOLARCOLLECTORPERFORMANCE_FLATPLATE_FIELDENUMS_HXX
