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

#ifndef UTILITIES_IDD_FAULTMODEL_FOULING_COIL_FIELDENUMS_HXX
#define UTILITIES_IDD_FAULTMODEL_FOULING_COIL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FaultModel_Fouling_CoilFields
 *  \brief Enumeration of FaultModel:Fouling:Coil's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FaultModel_Fouling_CoilFields, )
#else
class FaultModel_Fouling_CoilFields: public ::EnumBase<FaultModel_Fouling_CoilFields> {
 public: 
  enum domain 
  {
Name, CoilName, AvailabilityScheduleName, SeverityScheduleName, FoulingInputMethod, UAFouled, WaterSideFoulingFactor, AirSideFoulingFactor, OutsideCoilSurfaceArea, InsidetoOutsideCoilSurfaceAreaRatio,   };
  FaultModel_Fouling_CoilFields()
   : EnumBase<FaultModel_Fouling_CoilFields>(Name) {} 
  FaultModel_Fouling_CoilFields(const std::string &t_name) 
   : EnumBase<FaultModel_Fouling_CoilFields>(t_name) {} 
  FaultModel_Fouling_CoilFields(int t_value) 
   : EnumBase<FaultModel_Fouling_CoilFields>(t_value) {} 
  static std::string enumName() 
  { return "FaultModel_Fouling_CoilFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FaultModel_Fouling_CoilFields>::value()); }
   private:
    friend class EnumBase<FaultModel_Fouling_CoilFields>;
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
{ FaultModel_Fouling_CoilFields::Name, "Name", "Name"},
{ FaultModel_Fouling_CoilFields::CoilName, "CoilName", "Coil Name"},
{ FaultModel_Fouling_CoilFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ FaultModel_Fouling_CoilFields::SeverityScheduleName, "SeverityScheduleName", "Severity Schedule Name"},
{ FaultModel_Fouling_CoilFields::FoulingInputMethod, "FoulingInputMethod", "Fouling Input Method"},
{ FaultModel_Fouling_CoilFields::UAFouled, "UAFouled", "UAFouled"},
{ FaultModel_Fouling_CoilFields::WaterSideFoulingFactor, "WaterSideFoulingFactor", "Water Side Fouling Factor"},
{ FaultModel_Fouling_CoilFields::AirSideFoulingFactor, "AirSideFoulingFactor", "Air Side Fouling Factor"},
{ FaultModel_Fouling_CoilFields::OutsideCoilSurfaceArea, "OutsideCoilSurfaceArea", "Outside Coil Surface Area"},
{ FaultModel_Fouling_CoilFields::InsidetoOutsideCoilSurfaceAreaRatio, "InsidetoOutsideCoilSurfaceAreaRatio", "Inside to Outside Coil Surface Area Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const FaultModel_Fouling_CoilFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FaultModel_Fouling_CoilFields> OptionalFaultModel_Fouling_CoilFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAULTMODEL_FOULING_COIL_FIELDENUMS_HXX
