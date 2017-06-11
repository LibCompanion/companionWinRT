/*
 * CompanionWinRT is a Windows Runtime wrapper for libCompanion.
 * Copyright (C) 2017 Dimitri Kotlovsky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <companion/util/CompanionError.h>

#include "CompanionUtils.h"

namespace CompanionWinRT
{
    
    /*
     * C++/CX supports a set of standard exceptions that represent typical HRESULT errors. Each standard exception
     * derives from Platform::COMException, which in turn derives from Platform::Exception. When you throw an
     * exception across the ABI boundary, you must throw one of the standard exceptions. You can't derive your own
     * exception type from Platform::Exception. To throw a custom exception, use a user-defined HRESULT to construct
     * a COMException object. There's no way to specify a custom Message in a COMException. (via docs.microsoft.com)
     */


    /**
     * Enumeration class for error codes (user defined HRESULTs).
     */
    public enum class ErrorCode
    {
        unknown_error = 0x80000100, ///< Unknown error.
        image_not_found, ///< Image not found error.
        dimension_error, ///< Dimensions from given images are unequal.
        template_dimension_error, ///< Dimensions from template are wrong.
        feature_detector_not_found, ///< Given feature detector is not supported.
        descriptor_extractor_not_found, ///< Given descriptor extractor is not supported.
        descriptor_matcher_not_found, ///< Given descriptor matcher is not supported.
        wrong_model_type, ///< Given model class type is not supported for an image recognition search.
        invalid_companion_config, ///< Given configuration is invalid.
        video_src_not_set, ///< Given video source is not set.
        invalid_video_src, ///< Given video source is invalid (for example due to a wrong path).
        no_image_processing_algo_set, ///< No image processing algorithm is used.
        no_handler_set, ///< No callback handler is set.

        // additional error codes
        model_not_added, ///< Could not add model to Configuration.
        recognition_not_found, ///< Provided handle to CPUFeatureMatching object is null (nullptr)
        config_or_recognition_not_found, ///< Provided pointer to Configuration  or handle to CPUFeatureMatching object is null (nullptr)
        objectdetection_not_found, ///< Provided handle to ObjectDetection object is null (nullptr)
        model_path_not_set ///< Provided handle to model path is null (nullptr)
    };

    /**
     * This class defines necessary functions for error handling.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class CompanionErrorUWP sealed
    {
        public:

            /**
             * Returns the error message of the corresponding error code.
             *
             * @param code The error code
             * @return Error message.
             */
            static Platform::String^ getError(ErrorCode code)
            {

                Platform::String^ error = "Unknown Error";

                switch (code)
                {
                    case ErrorCode::descriptor_extractor_not_found :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::descriptor_extractor_not_found));
                        break;
                    case ErrorCode::descriptor_matcher_not_found :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::descriptor_matcher_not_found));
                        break;
                    case ErrorCode::dimension_error :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::dimension_error));
                        break;
                    case ErrorCode::feature_detector_not_found :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::feature_detector_not_found));
                        break;
                    case ErrorCode::image_not_found :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::image_not_found));
                        break;
                    case ErrorCode::template_dimension_error :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::template_dimension_error));
                        break;
                    case ErrorCode::wrong_model_type :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::wrong_model_type));
                        break;
                    case ErrorCode::invalid_companion_config :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::invalid_companion_config));
                        break;
                    case ErrorCode::video_src_not_set :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::video_src_not_set));
                        break;
                    case ErrorCode::invalid_video_src :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::invalid_video_src));
                        break;
                    case ErrorCode::no_image_processing_algo_set :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::no_image_processing_algo_set));
                        break;
                    case ErrorCode::no_handler_set :
                        error = ss2ps(Companion::Error::getError(Companion::Error::Code::no_handler_set));
                        break;
                    case ErrorCode::model_not_added :
                        error = "Could not add model to configuration.";
                        break;
                    case ErrorCode::recognition_not_found :
                        error = "The handle to the CPUFeatureMatching object is null.";
                        break;
                    case ErrorCode::config_or_recognition_not_found :
                        error = "At least one of the provided pointers/handles to the 'Configuration' and 'CPUFeatureMatching' objects is null.";
                        break;
                    case ErrorCode::objectdetection_not_found :
                        error = "The handle that points to the 'ObjectDetection' objects is null.";
                        break;
                    case ErrorCode::model_path_not_set :
                        error = "The handle that points to the model path is null.";
                        break;
                }

                return error;
            }

        private:
            CompanionErrorUWP(); // This type can't be constructed
    };

    /**
     * Returns the HRESULT error code of the corresponding Companion error code.
     *
     * @param code The companion error code
     * @return WinRT compatible HRESULT error code.
     */
    inline ErrorCode getErrorCode(Companion::Error::Code code)
    {
        ErrorCode error = ErrorCode::unknown_error;

        switch (code)
        {
            case Companion::Error::Code::descriptor_extractor_not_found :
                error = ErrorCode::descriptor_extractor_not_found;
                break;
            case Companion::Error::Code::descriptor_matcher_not_found :
                error = ErrorCode::descriptor_matcher_not_found;
                break;
            case Companion::Error::Code::dimension_error :
                error = ErrorCode::dimension_error;
                break;
            case Companion::Error::Code::feature_detector_not_found :
                error = ErrorCode::feature_detector_not_found;
                break;
            case Companion::Error::Code::image_not_found :
                error = ErrorCode::image_not_found;
                break;
            case Companion::Error::Code::template_dimension_error :
                error = ErrorCode::template_dimension_error;
                break;
            case Companion::Error::Code::wrong_model_type :
                error = ErrorCode::wrong_model_type;
                break;
            case Companion::Error::Code::invalid_companion_config :
                error = ErrorCode::invalid_companion_config;
                break;
            case Companion::Error::Code::video_src_not_set :
                error = ErrorCode::video_src_not_set;
                break;
            case Companion::Error::Code::invalid_video_src :
                error = ErrorCode::invalid_video_src;
                break;
            case Companion::Error::Code::no_image_processing_algo_set :
                error = ErrorCode::no_image_processing_algo_set;
                break;
            case Companion::Error::Code::no_handler_set :
                error = ErrorCode::no_handler_set;
                break;
        }

        return error;
    }

}
