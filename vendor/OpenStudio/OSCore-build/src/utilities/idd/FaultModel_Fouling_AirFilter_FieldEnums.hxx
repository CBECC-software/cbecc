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

#ifndef UTILITIES_IDD_FAULTMODEL_FOULING_AIRFILTER_FIELDENUMS_HXX
#define UTILITIES_IDD_FAULTMODEL_FOULING_AIRFILTER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FaultModel_Fouling_AirFilterFields
 *  \brief Enumeration of FaultModel:Fouling:AirFilter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FaultModel_Fouling_AirFilterFields, )
#else
class FaultModel_Fouling_AirFilterFields: public ::EnumBase<FaultModel_Fouling_AirFilterFields> {
 public: 
  enum domain 
  {
Name, FanObjectType, FanName, AvailabilityScheduleName, PressureFractionScheduleName, FanCurveName,   };
  FaultModel_Fouling_AirFilterFields()
   : EnumBase<FaultModel_Fouling_AirFilterFields>(Name) {} 
  FaultModel_Fouling_AirFilterFields(const std::string &t_name) 
   : EnumBase<FaultModel_Fouling_AirFilterFields>(t_name) {} 
  FaultModel_Fouling_AirFilterFields(int t_value) 
   : EnumBase<FaultModel_Fouling_AirFilterFields>(t_value) {} 
  static std::string enumName() 
  { return "FaultModel_Fouling_AirFilterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FaultModel_Fouling_AirFilterFields>::value()); }
   private:
    friend class EnumBase<FaultModel_Fouling_AirFilterFields>;
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
{ FaultModel_Fouling_AirFilterFields::Name, "Name", "Name"},
{ FaultModel_Fouling_AirFilterFields::FanObjectType, "FanObjectType", "Fan Object Type"},
{ FaultModel_Fouling_AirFilterFields::FanName, "FanName", "Fan Name"},
{ FaultModel_Fouling_AirFilterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ FaultModel_Fouling_AirFilterFields::PressureFractionScheduleName, "PressureFractionScheduleName", "Pressure Fraction Schedule Name"},
{ FaultModel_Fouling_AirFilterFields::FanCurveName, "FanCurveName", "Fan Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const FaultModel_Fouling_AirFilterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FaultModel_Fouling_AirFilterFields> OptionalFaultModel_Fouling_AirFilterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAULTMODEL_FOULING_AIRFILTER_FIELDENUMS_HXX
