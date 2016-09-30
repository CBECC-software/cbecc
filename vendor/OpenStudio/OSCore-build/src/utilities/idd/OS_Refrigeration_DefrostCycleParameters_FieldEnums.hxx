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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_DEFROSTCYCLEPARAMETERS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_DEFROSTCYCLEPARAMETERS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_DefrostCycleParametersFields
 *  \brief Enumeration of OS:Refrigeration:DefrostCycleParameters's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_DefrostCycleParametersFields, )
#else
class OS_Refrigeration_DefrostCycleParametersFields: public ::EnumBase<OS_Refrigeration_DefrostCycleParametersFields> {
 public: 
  enum domain 
  {
Handle, Name, DurationofDefrostCycle, DripDownTime, Defrost1HourStartTime, Defrost1MinuteStartTime, Defrost2HourStartTime, Defrost2MinuteStartTime, Defrost3HourStartTime, Defrost3MinuteStartTime, Defrost4HourStartTime, Defrost4MinuteStartTime, Defrost5HourStartTime, Defrost5MinuteStartTime, Defrost6HourStartTime, Defrost6MinuteStartTime, Defrost7HourStartTime, Defrost7MinuteStartTime, Defrost8HourStartTime, Defrost8MinuteStartTime,   };
  OS_Refrigeration_DefrostCycleParametersFields()
   : EnumBase<OS_Refrigeration_DefrostCycleParametersFields>(Handle) {} 
  OS_Refrigeration_DefrostCycleParametersFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_DefrostCycleParametersFields>(t_name) {} 
  OS_Refrigeration_DefrostCycleParametersFields(int t_value) 
   : EnumBase<OS_Refrigeration_DefrostCycleParametersFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_DefrostCycleParametersFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_DefrostCycleParametersFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_DefrostCycleParametersFields>;
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
{ OS_Refrigeration_DefrostCycleParametersFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_DefrostCycleParametersFields::Name, "Name", "Name"},
{ OS_Refrigeration_DefrostCycleParametersFields::DurationofDefrostCycle, "DurationofDefrostCycle", "Duration of Defrost Cycle"},
{ OS_Refrigeration_DefrostCycleParametersFields::DripDownTime, "DripDownTime", "Drip Down Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost1HourStartTime, "Defrost1HourStartTime", "Defrost 1 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost1MinuteStartTime, "Defrost1MinuteStartTime", "Defrost 1 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost2HourStartTime, "Defrost2HourStartTime", "Defrost 2 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost2MinuteStartTime, "Defrost2MinuteStartTime", "Defrost 2 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost3HourStartTime, "Defrost3HourStartTime", "Defrost 3 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost3MinuteStartTime, "Defrost3MinuteStartTime", "Defrost 3 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost4HourStartTime, "Defrost4HourStartTime", "Defrost 4 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost4MinuteStartTime, "Defrost4MinuteStartTime", "Defrost 4 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost5HourStartTime, "Defrost5HourStartTime", "Defrost 5 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost5MinuteStartTime, "Defrost5MinuteStartTime", "Defrost 5 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost6HourStartTime, "Defrost6HourStartTime", "Defrost 6 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost6MinuteStartTime, "Defrost6MinuteStartTime", "Defrost 6 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost7HourStartTime, "Defrost7HourStartTime", "Defrost 7 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost7MinuteStartTime, "Defrost7MinuteStartTime", "Defrost 7 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost8HourStartTime, "Defrost8HourStartTime", "Defrost 8 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost8MinuteStartTime, "Defrost8MinuteStartTime", "Defrost 8 Minute Start Time"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_DefrostCycleParametersFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_DefrostCycleParametersFields> OptionalOS_Refrigeration_DefrostCycleParametersFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_DEFROSTCYCLEPARAMETERS_FIELDENUMS_HXX
