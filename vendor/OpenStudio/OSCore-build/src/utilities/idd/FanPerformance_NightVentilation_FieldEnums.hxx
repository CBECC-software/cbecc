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

#ifndef UTILITIES_IDD_FANPERFORMANCE_NIGHTVENTILATION_FIELDENUMS_HXX
#define UTILITIES_IDD_FANPERFORMANCE_NIGHTVENTILATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FanPerformance_NightVentilationFields
 *  \brief Enumeration of FanPerformance:NightVentilation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FanPerformance_NightVentilationFields, )
#else
class FanPerformance_NightVentilationFields: public ::EnumBase<FanPerformance_NightVentilationFields> {
 public: 
  enum domain 
  {
FanName, FanTotalEfficiency, PressureRise, MaximumFlowRate, MotorEfficiency, MotorinAirstreamFraction,   };
  FanPerformance_NightVentilationFields()
   : EnumBase<FanPerformance_NightVentilationFields>(FanName) {} 
  FanPerformance_NightVentilationFields(const std::string &t_name) 
   : EnumBase<FanPerformance_NightVentilationFields>(t_name) {} 
  FanPerformance_NightVentilationFields(int t_value) 
   : EnumBase<FanPerformance_NightVentilationFields>(t_value) {} 
  static std::string enumName() 
  { return "FanPerformance_NightVentilationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FanPerformance_NightVentilationFields>::value()); }
   private:
    friend class EnumBase<FanPerformance_NightVentilationFields>;
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
{ FanPerformance_NightVentilationFields::FanName, "FanName", "Fan Name"},
{ FanPerformance_NightVentilationFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ FanPerformance_NightVentilationFields::PressureRise, "PressureRise", "Pressure Rise"},
{ FanPerformance_NightVentilationFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ FanPerformance_NightVentilationFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ FanPerformance_NightVentilationFields::MotorinAirstreamFraction, "MotorinAirstreamFraction", "Motor in Airstream Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const FanPerformance_NightVentilationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FanPerformance_NightVentilationFields> OptionalFanPerformance_NightVentilationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FANPERFORMANCE_NIGHTVENTILATION_FIELDENUMS_HXX
