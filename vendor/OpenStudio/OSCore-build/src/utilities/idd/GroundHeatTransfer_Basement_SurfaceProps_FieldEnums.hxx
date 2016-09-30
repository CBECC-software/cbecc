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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_SURFACEPROPS_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_SURFACEPROPS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Basement_SurfacePropsFields
 *  \brief Enumeration of GroundHeatTransfer:Basement:SurfaceProps's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Basement_SurfacePropsFields, )
#else
class GroundHeatTransfer_Basement_SurfacePropsFields: public ::EnumBase<GroundHeatTransfer_Basement_SurfacePropsFields> {
 public: 
  enum domain 
  {
ALBEDO_SurfacealbedoforNosnowconditions, ALBEDO_Surfacealbedoforsnowconditions, EPSLN_SurfaceemissivityNoSnow, EPSLN_SurfaceemissivitywithSnow, VEGHT_SurfaceroughnessNosnowconditions, VEGHT_SurfaceroughnessSnowconditions, PET_FlagPotentialevapotranspirationon,   };
  GroundHeatTransfer_Basement_SurfacePropsFields()
   : EnumBase<GroundHeatTransfer_Basement_SurfacePropsFields>(ALBEDO_SurfacealbedoforNosnowconditions) {} 
  GroundHeatTransfer_Basement_SurfacePropsFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Basement_SurfacePropsFields>(t_name) {} 
  GroundHeatTransfer_Basement_SurfacePropsFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Basement_SurfacePropsFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Basement_SurfacePropsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Basement_SurfacePropsFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Basement_SurfacePropsFields>;
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
{ GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_SurfacealbedoforNosnowconditions, "ALBEDO_SurfacealbedoforNosnowconditions", "ALBEDO: Surface albedo for No snow conditions"},
{ GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_Surfacealbedoforsnowconditions, "ALBEDO_Surfacealbedoforsnowconditions", "ALBEDO: Surface albedo for snow conditions"},
{ GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivityNoSnow, "EPSLN_SurfaceemissivityNoSnow", "EPSLN: Surface emissivity No Snow"},
{ GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivitywithSnow, "EPSLN_SurfaceemissivitywithSnow", "EPSLN: Surface emissivity with Snow"},
{ GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessNosnowconditions, "VEGHT_SurfaceroughnessNosnowconditions", "VEGHT: Surface roughness No snow conditions"},
{ GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessSnowconditions, "VEGHT_SurfaceroughnessSnowconditions", "VEGHT: Surface roughness Snow conditions"},
{ GroundHeatTransfer_Basement_SurfacePropsFields::PET_FlagPotentialevapotranspirationon, "PET_FlagPotentialevapotranspirationon", "PET: Flag Potential evapotranspiration on?"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Basement_SurfacePropsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Basement_SurfacePropsFields> OptionalGroundHeatTransfer_Basement_SurfacePropsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_SURFACEPROPS_FIELDENUMS_HXX
