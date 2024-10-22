#include "napi/native_api.h"

#undef LOG_DOMAIN
#undef LOG_TAG
#define TAG "CupsTest"
#define LOG_DOMAIN 0x0001
#define LOG_TAG TAG
#include <hilog/log.h>
#include "cups/cups.h"

static void enumPrinters() {
    auto print_dest = [](void *user_data, unsigned flags, cups_dest_t *dest) {
        if (dest->instance)
            OH_LOG_DEBUG(LOG_APP, "%{public}s%{public}s", dest->name, dest->instance);
        else
            OH_LOG_DEBUG(LOG_APP, "%{public}s", dest->name);

        return (1);
    };
    cupsEnumDests(CUPS_DEST_FLAGS_NONE, 1000, NULL, 0, 0, print_dest, NULL);
}

static napi_value DiscoverDevices(napi_env env, napi_callback_info info)
{
    OH_LOG_DEBUG(LOG_APP, "%{public}s", "in DiscoverPrinters");
    enumPrinters();
    return 0;
}

static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    return sum;

}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "discoverDevices", nullptr, DiscoverDevices, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "nvwo",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterNvwoModule(void)
{
    napi_module_register(&demoModule);
}
