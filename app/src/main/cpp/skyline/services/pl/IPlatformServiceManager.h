// SPDX-License-Identifier: MPL-2.0
// Copyright © 2020 Skyline Team and Contributors (https://github.com/skyline-emu/)

#pragma once

#include <kernel/types/KSharedMemory.h>
#include <services/serviceman.h>

namespace skyline {
    namespace constant {
        constexpr u32 FontSharedMemSize{0x1100000}; //!< The total size of the font shared memory
    }

    namespace service::pl {
        /**
         * @brief IPlatformServiceManager is used to access shared fonts
         * @url https://switchbrew.org/wiki/Shared_Database_services#pl:u.2C_pl:s
         */
        class IPlatformServiceManager : public BaseService {
          private:
            std::shared_ptr<kernel::type::KSharedMemory> fontSharedMem; //!< The KSharedMemory that stores the TTF data of all shared fonts

          public:
            IPlatformServiceManager(const DeviceState &state, ServiceManager &manager);

            /**
             * @brief Returns the loading state of the requested font
             * @url https://switchbrew.org/wiki/Shared_Database_services#GetLoadState
             */
            Result GetLoadState(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response);

            /**
             * @brief Returns the size of the requested font
             * @url https://switchbrew.org/wiki/Shared_Database_services#GetSize
             */
            Result GetSize(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response);

            /**
             * @brief Returns the offset in shared memory of the requested font
             * @url https://switchbrew.org/wiki/Shared_Database_services#GetSharedMemoryAddressOffset
             */
            Result GetSharedMemoryAddressOffset(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response);

            /**
             * @brief Returns a handle to the whole font shared memory
             * @url https://switchbrew.org/wiki/Shared_Database_services#GetSharedMemoryNativeHandle
             */
            Result GetSharedMemoryNativeHandle(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response);

            SERVICE_DECL(
                SFUNC(0x1, IPlatformServiceManager, GetLoadState),
                SFUNC(0x2, IPlatformServiceManager, GetSize),
                SFUNC(0x3, IPlatformServiceManager, GetSharedMemoryAddressOffset),
                SFUNC(0x4, IPlatformServiceManager, GetSharedMemoryNativeHandle)
            )
        };
    }
}
