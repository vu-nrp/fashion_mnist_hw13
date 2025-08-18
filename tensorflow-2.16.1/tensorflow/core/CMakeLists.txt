cmake_minimum_required(VERSION 3.7)

# Double colon in target name means ALIAS or IMPORTED target.
cmake_policy(SET CMP0028 NEW)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project(tensorflow-core-mix C CXX)

find_package(Protobuf REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(TENSORFLOW_SOURCE_DIR "" CACHE PATH
  "Directory that contains the TensorFlow project"
)
if(NOT TENSORFLOW_SOURCE_DIR)
  get_filename_component(TENSORFLOW_SOURCE_DIR
    "${CMAKE_CURRENT_LIST_DIR}/../../"
    ABSOLUTE
  )
endif()


## tensorflow-core proto files
file(GLOB_RECURSE TF_CORE_PROTO_FILES
    ${TF_SOURCE_DIR}/core/*.proto
)

set(Protobuf_IMPORT_DIRS ${TSL_SOURCE_DIR} ${XLA_DIR})

include(ProtobufGenerateDfpost)
include(EnableMsvcSystemInclude)
protobuf_generate_dfpost(TF_CORE_PROTO_SRCS TF_CORE_PROTO_HDRS ${TENSORFLOW_SOURCE_DIR} ${TF_CORE_PROTO_FILES})

set(TF_CORE_PROTOBUF_LIB "tensorflow-lib-protobuf")
add_library(${TF_CORE_PROTOBUF_LIB} STATIC ${TF_CORE_PROTO_SRCS} ${TF_CORE_PROTO_HDRS} ${TF_CORE_PROTO_FILES})

set_target_properties(${TF_CORE_PROTOBUF_LIB} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
enable_msvc_system_include(${TF_CORE_PROTOBUF_LIB})
target_include_directories(${TF_CORE_PROTOBUF_LIB}
SYSTEM
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${TF_CORE_PROTOBUF_LIB}
PRIVATE
    tsl-lib-protobuf
    xla-lib-protobuf
    ${Protobuf_LIBRARIES}
)






set(TF_SOURCE_DIR "${TENSORFLOW_SOURCE_DIR}/tensorflow")
file(GLOB_RECURSE TF_CORE_SOURCES
    ${TF_SOURCE_DIR}/core/*.h
    ${TF_SOURCE_DIR}/c/*.h

    ${TF_SOURCE_DIR}/c/eager/*.cc

    ${TF_SOURCE_DIR}/core/activity_watcher/*.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/*.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/context.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/core.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/custom_device_op_handler.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/custom_device.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/eager_executor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/eager_operation.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/execute_node.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/execute.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/placement_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/small_constants_optimizer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/summary_optimizer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/tensor_handle.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eager/tensor_handle_data.cc

    ${TF_SOURCE_DIR}/core/common_runtime/gpu/gpu_id_manager.cc

    ${TF_SOURCE_DIR}/core/common_runtime/accumulate_n_optimizer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/all_to_all.cc
    ${TF_SOURCE_DIR}/core/common_runtime/arg_ret_placement.cc
    ${TF_SOURCE_DIR}/core/common_runtime/base_collective_executor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/buf_rendezvous.cc
    ${TF_SOURCE_DIR}/core/common_runtime/build_graph_options.cc
    ${TF_SOURCE_DIR}/core/common_runtime/collective_executor_mgr.cc
    ${TF_SOURCE_DIR}/core/common_runtime/collective_param_resolver_local.cc
    ${TF_SOURCE_DIR}/core/common_runtime/collective_rma_local.cc
    # ${TF_SOURCE_DIR}/core/common_runtime/collective_test_util.cc
    ${TF_SOURCE_DIR}/core/common_runtime/collective_util.cc
    ${TF_SOURCE_DIR}/core/common_runtime/colocate_predecessor_trees_pass.cc
    ${TF_SOURCE_DIR}/core/common_runtime/colocation_graph.cc
    ${TF_SOURCE_DIR}/core/common_runtime/composite_device.cc
    ${TF_SOURCE_DIR}/core/common_runtime/constant_folding.cc
    ${TF_SOURCE_DIR}/core/common_runtime/copy_tensor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/cost_measurement_registry.cc
    ${TF_SOURCE_DIR}/core/common_runtime/cost_util.cc
    ${TF_SOURCE_DIR}/core/common_runtime/costmodel_manager.cc
    ${TF_SOURCE_DIR}/core/common_runtime/debugger_state_interface.cc
    ${TF_SOURCE_DIR}/core/common_runtime/device_mgr.cc
    ${TF_SOURCE_DIR}/core/common_runtime/device_propagation.cc
    ${TF_SOURCE_DIR}/core/common_runtime/device_resolver_local.cc
    ${TF_SOURCE_DIR}/core/common_runtime/device_set.cc
    ${TF_SOURCE_DIR}/core/common_runtime/direct_session.cc
    ${TF_SOURCE_DIR}/core/common_runtime/dynamic_device_mgr.cc
    ${TF_SOURCE_DIR}/core/common_runtime/eval_const_tensor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/executor_factory.cc
    ${TF_SOURCE_DIR}/core/common_runtime/executor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/function_body.cc
    ${TF_SOURCE_DIR}/core/common_runtime/function_def_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/function_optimization_registry.cc
    # ${TF_SOURCE_DIR}/core/common_runtime/function_testlib.cc
    ${TF_SOURCE_DIR}/core/common_runtime/function_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/function.cc
    ${TF_SOURCE_DIR}/core/common_runtime/gradients.cc
    # ${TF_SOURCE_DIR}/core/common_runtime/graph_constructor_fuzz.cc
    ${TF_SOURCE_DIR}/core/common_runtime/graph_constructor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/graph_def_builder_util.cc
    ${TF_SOURCE_DIR}/core/common_runtime/graph_execution_state.cc
    ${TF_SOURCE_DIR}/core/common_runtime/graph_optimizer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/graph_runner.cc
    ${TF_SOURCE_DIR}/core/common_runtime/graph_view.cc
    ${TF_SOURCE_DIR}/core/common_runtime/hierarchical_tree_broadcaster.cc
    ${TF_SOURCE_DIR}/core/common_runtime/immutable_executor_state.cc
    ${TF_SOURCE_DIR}/core/common_runtime/inline_function_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/input_colocation_exemption_registry.cc
    ${TF_SOURCE_DIR}/core/common_runtime/inspecting_placer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/int32_fulltype.cc
    ${TF_SOURCE_DIR}/core/common_runtime/isolate_placer_inspection_required_ops_pass.cc
    # ${TF_SOURCE_DIR}/core/common_runtime/kernel_benchmark_testlib.cc
    ${TF_SOURCE_DIR}/core/common_runtime/layout_pass_util.cc
    ${TF_SOURCE_DIR}/core/common_runtime/local_device.cc
    ${TF_SOURCE_DIR}/core/common_runtime/local_session_selection.cc
    ${TF_SOURCE_DIR}/core/common_runtime/lower_case_op.cc
    ${TF_SOURCE_DIR}/core/common_runtime/lower_function_call_inline_policy.cc
    ${TF_SOURCE_DIR}/core/common_runtime/lower_function_call_op.cc
    ${TF_SOURCE_DIR}/core/common_runtime/lower_functional_ops.cc
    ${TF_SOURCE_DIR}/core/common_runtime/lower_if_op.cc
    ${TF_SOURCE_DIR}/core/common_runtime/lower_while_op.cc
    ${TF_SOURCE_DIR}/core/common_runtime/memory_types.cc
    ${TF_SOURCE_DIR}/core/common_runtime/mkl_cpu_allocator.cc
    ${TF_SOURCE_DIR}/core/common_runtime/mkl_layout_pass.cc
    ${TF_SOURCE_DIR}/core/common_runtime/no_op_cost_measurement.cc
    ${TF_SOURCE_DIR}/core/common_runtime/node_file_writer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/null_request_cost_accessor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/optimization_registry.cc
    ${TF_SOURCE_DIR}/core/common_runtime/optimize_cross_host_control_deps.cc
    ${TF_SOURCE_DIR}/core/common_runtime/optimize_function_graph_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/optimized_function_graph_info.cc
    ${TF_SOURCE_DIR}/core/common_runtime/parallel_concat_optimizer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/partitioning_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/permuter.cc
    ${TF_SOURCE_DIR}/core/common_runtime/placer_inspection_required_ops_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/placer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/pool_allocator.cc
    ${TF_SOURCE_DIR}/core/common_runtime/process_function_library_runtime.cc
    ${TF_SOURCE_DIR}/core/common_runtime/process_state.cc
    ${TF_SOURCE_DIR}/core/common_runtime/process_util.cc
    ${TF_SOURCE_DIR}/core/common_runtime/propagator_debug_utils.cc
    ${TF_SOURCE_DIR}/core/common_runtime/propagator_state.cc
    ${TF_SOURCE_DIR}/core/common_runtime/quantize_training.cc
    ${TF_SOURCE_DIR}/core/common_runtime/renamed_device.cc
    ${TF_SOURCE_DIR}/core/common_runtime/rendezvous_mgr.cc
    ${TF_SOURCE_DIR}/core/common_runtime/rendezvous_util.cc
    ${TF_SOURCE_DIR}/core/common_runtime/replicate_constants_pass.cc
    ${TF_SOURCE_DIR}/core/common_runtime/replicate_per_replica_nodes.cc
    ${TF_SOURCE_DIR}/core/common_runtime/request_cost_accessor_registry.cc
    ${TF_SOURCE_DIR}/core/common_runtime/request_cost.cc
    ${TF_SOURCE_DIR}/core/common_runtime/ring_alg.cc
    ${TF_SOURCE_DIR}/core/common_runtime/ring_gatherer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/ring_reducer.cc
    ${TF_SOURCE_DIR}/core/common_runtime/scoped_allocator_mgr.cc
    ${TF_SOURCE_DIR}/core/common_runtime/scoped_allocator.cc
    ${TF_SOURCE_DIR}/core/common_runtime/serving_device_selector_policies.cc
    ${TF_SOURCE_DIR}/core/common_runtime/serving_device_selector.cc
    ${TF_SOURCE_DIR}/core/common_runtime/session_factory.cc
    ${TF_SOURCE_DIR}/core/common_runtime/session_options.cc
    ${TF_SOURCE_DIR}/core/common_runtime/session_state.cc
    ${TF_SOURCE_DIR}/core/common_runtime/session.cc
    ${TF_SOURCE_DIR}/core/common_runtime/shape_refiner.cc
    ${TF_SOURCE_DIR}/core/common_runtime/simple_propagator_state.cc
    ${TF_SOURCE_DIR}/core/common_runtime/single_threaded_cpu_device.cc
    ${TF_SOURCE_DIR}/core/common_runtime/single_threaded_executor.cc
    ${TF_SOURCE_DIR}/core/common_runtime/stats_publisher_interface.cc
    ${TF_SOURCE_DIR}/core/common_runtime/step_stats_collector.cc
    # ${TF_SOURCE_DIR}/core/common_runtime/testlib_ops.cc
    ${TF_SOURCE_DIR}/core/common_runtime/threadpool_device_factory.cc
    ${TF_SOURCE_DIR}/core/common_runtime/threadpool_device.cc
    ${TF_SOURCE_DIR}/core/common_runtime/type_inference.cc

    ${TF_SOURCE_DIR}/core/distributed_runtime/coordination/coordination_service_barrier_proxy.cc

    ${TF_SOURCE_DIR}/core/distributed_runtime/eager/remote_copy_node.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/eager/cluster_function_library_runtime.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/eager/eager_service_impl.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/eager/remote_copy_node.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/eager/remote_execute_node.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/eager/remote_mgr.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/eager/remote_tensor_handle_data.cc

    ${TF_SOURCE_DIR}/core/distributed_runtime/preemption/check_preemption_op_kernel.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/preemption/check_preemption_op.cc

    ${TF_SOURCE_DIR}/core/distributed_runtime/base_rendezvous_mgr.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/cancellable_call.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/cluster_function_library_runtime.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/collective_param_resolver_distributed.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/collective_rma_distributed.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/device_resolver_distributed.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/graph_mgr.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/local_master.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/master_session.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/master.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/message_wrappers.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/partial_run_mgr.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/recent_request_ids.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/remote_device.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/request_id.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/rpc_collective_executor_mgr.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/scheduler.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/server_lib.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/session_mgr.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/tensor_coding.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/worker_cache_logger.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/worker_cache_partial.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/worker_session.cc
    ${TF_SOURCE_DIR}/core/distributed_runtime/worker.cc


    ${TF_SOURCE_DIR}/core/grappler/devices.cc
    # ${TF_SOURCE_DIR}/core/grappler/graph_topology_view_test.cc
    ${TF_SOURCE_DIR}/core/grappler/graph_topology_view.cc
    # ${TF_SOURCE_DIR}/core/grappler/graph_view_test.cc
    ${TF_SOURCE_DIR}/core/grappler/graph_view.cc
    # ${TF_SOURCE_DIR}/core/grappler/grappler_item_builder_test.cc
    ${TF_SOURCE_DIR}/core/grappler/grappler_item_builder.cc
    # ${TF_SOURCE_DIR}/core/grappler/grappler_item_test.cc
    ${TF_SOURCE_DIR}/core/grappler/grappler_item.cc
    # ${TF_SOURCE_DIR}/core/grappler/mutable_graph_view_test.cc
    ${TF_SOURCE_DIR}/core/grappler/mutable_graph_view.cc
    ${TF_SOURCE_DIR}/core/grappler/op_types.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils.cc
    # ${TF_SOURCE_DIR}/core/grappler/clusters/*.cc
    ${TF_SOURCE_DIR}/core/grappler/clusters/cluster.cc
    # ${TF_SOURCE_DIR}/core/grappler/clusters/single_machine.cc
    ${TF_SOURCE_DIR}/core/grappler/clusters/utils.cc
    ${TF_SOURCE_DIR}/core/grappler/clusters/virtual_cluster.cc

    # ${TF_SOURCE_DIR}/core/grappler/costs/analytical_cost_estimator_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/analytical_cost_estimator.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/cost_estimator_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/cost_estimator.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/graph_memory_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/graph_memory.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/graph_properties_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/graph_properties.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/measuring_cost_estimator.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/op_level_cost_estimator_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/op_level_cost_estimator.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/robust_stats_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/robust_stats.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/utils_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/utils.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/virtual_placer_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/virtual_placer.cc
    # ${TF_SOURCE_DIR}/core/grappler/costs/virtual_scheduler_test.cc
    ${TF_SOURCE_DIR}/core/grappler/costs/virtual_scheduler.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/canonicalizer_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/canonicalizer.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/colocation_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/colocation.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/frame_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/frame.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/functions_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/functions.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/graph_view_internal_test.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/graph_view_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/graph_view.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/grappler_test_test.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/grappler_test.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/pattern_utils_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/pattern_utils.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/scc_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/scc.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/symbolic_shapes_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/symbolic_shapes.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/topological_sort_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/topological_sort.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/tpu_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/tpu.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/transitive_fanin_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/transitive_fanin.cc
    # ${TF_SOURCE_DIR}/core/grappler/utils/traversal_test.cc
    ${TF_SOURCE_DIR}/core/grappler/utils/traversal.cc
    ${TF_SOURCE_DIR}/core/grappler/optimizers/*.cc
    ${TF_SOURCE_DIR}/core/grappler/verifiers/*.cc
    ${TF_SOURCE_DIR}/core/data/*.cc


    ${TF_SOURCE_DIR}/core/framework/tensor.cc
    ${TF_SOURCE_DIR}/core/framework/function.cc
    ${TF_SOURCE_DIR}/core/framework/device_factory.cc
    ${TF_SOURCE_DIR}/core/framework/*.cc

    ${TF_SOURCE_DIR}/core/platform/cpu_feature_guard.cc
    ${TF_SOURCE_DIR}/core/platform/tensor_coding.cc
    ${TF_SOURCE_DIR}/core/platform/platform_strings.cc

    ${TF_SOURCE_DIR}/core/profiler/convert/xplane_to_step_stats.cc
    ${TF_SOURCE_DIR}/core/profiler/convert/op_metrics_db_combiner.cc

    ${TF_SOURCE_DIR}/core/profiler/utils/cost_utils.cc
    # ${TF_SOURCE_DIR}/core/profiler/utils/derived_timeline.cc
    # ${TF_SOURCE_DIR}/core/profiler/utils/device_caps_utils.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/diagnostics.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/event_span.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/gpu_event_stats.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/hardware_type_utils.cc
    # ${TF_SOURCE_DIR}/core/profiler/utils/hlo_module_map.cc
    # ${TF_SOURCE_DIR}/core/profiler/utils/hlo_proto_map.cc
    # ${TF_SOURCE_DIR}/core/profiler/utils/hlo_proto_to_module.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/kernel_stats_utils.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/op_metrics_db_utils.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/op_utils.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/step_intersection.cc
    ${TF_SOURCE_DIR}/core/profiler/utils/tfstreamz_utils.cc

    ${TF_SOURCE_DIR}/core/protobuf/*.h
    ${TF_SOURCE_DIR}/core/protobuf/*.cc

    ${TF_SOURCE_DIR}/core/config/flag_defs.cc
    ${TF_SOURCE_DIR}/core/config/flags.cc
    ${TF_SOURCE_DIR}/core/util/bcast.cc
    ${TF_SOURCE_DIR}/core/util/dump_graph.cc
    ${TF_SOURCE_DIR}/core/util/batch_util.cc
    ${TF_SOURCE_DIR}/core/util/debug_data_dumper.cc
    ${TF_SOURCE_DIR}/core/util/equal_graph_def.cc
    ${TF_SOURCE_DIR}/core/util/example_*.cc
    ${TF_SOURCE_DIR}/core/util/einsum_op_util.cc
    ${TF_SOURCE_DIR}/core/util/guarded_philox_random.cc
    ${TF_SOURCE_DIR}/core/util/matmul_autotune.cc
    ${TF_SOURCE_DIR}/core/util/mirror_pad_mode.cc
    ${TF_SOURCE_DIR}/core/util/padding.cc
    ${TF_SOURCE_DIR}/core/util/port.cc
    ${TF_SOURCE_DIR}/core/util/proto/*.cc
    ${TF_SOURCE_DIR}/core/util/quantization/*.cc
    ${TF_SOURCE_DIR}/core/util/ragged_to_dense_util.cc
    ${TF_SOURCE_DIR}/core/util/saved_tensor_slice_util.cc
    ${TF_SOURCE_DIR}/core/util/sparse/*.cc
    ${TF_SOURCE_DIR}/core/util/strided_slice_op.cc
    ${TF_SOURCE_DIR}/core/util/tensor_bundle/*.cc
    ${TF_SOURCE_DIR}/core/util/tensor_*.cc
    ${TF_SOURCE_DIR}/core/util/work_sharder.cc
    ${TF_SOURCE_DIR}/core/util/util.cc
    ${TF_SOURCE_DIR}/core/util/xla_config_registry.cc



    # ${TF_SOURCE_DIR}/core/kernels/*.cc
[[
    ${TF_SOURCE_DIR}/core/kernels/batching_util/adaptive_shared_batch_scheduler.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/basic_batch_scheduler.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/batch_input_task.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/batch_resource_base.cc
    ${TF_SOURCE_DIR}/core/kernels/batching_util/batch_resource_base.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/batch_scheduler.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/bounded_executor.cc
    ${TF_SOURCE_DIR}/core/kernels/batching_util/bounded_executor.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/concat_split_util.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/fake_clock_env.cc
    ${TF_SOURCE_DIR}/core/kernels/batching_util/fake_clock_env.h
    # ${TF_SOURCE_DIR}/core/kernels/batching_util/input_split_metadata.cc
    ${TF_SOURCE_DIR}/core/kernels/batching_util/input_split_metadata.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/periodic_function.cc
    ${TF_SOURCE_DIR}/core/kernels/batching_util/periodic_function.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/serial_device_batch_scheduler.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/shared_batch_scheduler.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/threadsafe_status.cc
    ${TF_SOURCE_DIR}/core/kernels/batching_util/threadsafe_status.h
    ${TF_SOURCE_DIR}/core/kernels/batching_util/warmup.cc
    ${TF_SOURCE_DIR}/core/kernels/batching_util/warmup.h


    ${TF_SOURCE_DIR}/core/kernels/aggregate_ops_cpu.h
    # ${TF_SOURCE_DIR}/core/kernels/aggregate_ops_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/aggregate_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/aggregate_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/argmax_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/argmax_op.cc
    ${TF_SOURCE_DIR}/core/kernels/argmax_op.h
    ${TF_SOURCE_DIR}/core/kernels/as_string_op.cc
    ${TF_SOURCE_DIR}/core/kernels/assign_op.h
    ${TF_SOURCE_DIR}/core/kernels/autotune_conv_impl.h
    # ${TF_SOURCE_DIR}/core/kernels/avgpooling_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/avgpooling_op.cc
    ${TF_SOURCE_DIR}/core/kernels/avgpooling_op.h
    ${TF_SOURCE_DIR}/core/kernels/barrier_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/base64_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/batch_kernels.cc
    ${TF_SOURCE_DIR}/core/kernels/batch_kernels.h
    # ${TF_SOURCE_DIR}/core/kernels/batch_norm_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/batch_norm_op.cc
    ${TF_SOURCE_DIR}/core/kernels/batch_norm_op.h
    ${TF_SOURCE_DIR}/core/kernels/batch_util.h
    ${TF_SOURCE_DIR}/core/kernels/batchtospace_op.cc
    ${TF_SOURCE_DIR}/core/kernels/bcast_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/betainc_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/betainc_op.cc
    ${TF_SOURCE_DIR}/core/kernels/betainc_op.h
    # ${TF_SOURCE_DIR}/core/kernels/bias_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/bias_op_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/bias_op.cc
    ${TF_SOURCE_DIR}/core/kernels/bias_op.h
    # ${TF_SOURCE_DIR}/core/kernels/bincount_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/bincount_op.cc
    ${TF_SOURCE_DIR}/core/kernels/bincount_op.h
    # ${TF_SOURCE_DIR}/core/kernels/broadcast_to_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/broadcast_to_op.cc
    ${TF_SOURCE_DIR}/core/kernels/broadcast_to_op.h
    # ${TF_SOURCE_DIR}/core/kernels/bucketize_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/bucketize_op.cc
    ${TF_SOURCE_DIR}/core/kernels/bucketize_op.h
    ${TF_SOURCE_DIR}/core/kernels/BUILD
    ${TF_SOURCE_DIR}/core/kernels/candidate_sampler_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/cast_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_bfloat.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_bool.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_complex64.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_complex128.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_double.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_float.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_float8.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_half.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_int4.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_int8.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_int16.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_int32.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_int64.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_uint4.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_uint8.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_uint16.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_uint32.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl_uint64.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op_impl.h
    ${TF_SOURCE_DIR}/core/kernels/cast_op.cc
    ${TF_SOURCE_DIR}/core/kernels/cast_op.h
    # ${TF_SOURCE_DIR}/core/kernels/check_numerics_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/check_numerics_op.cc
    ${TF_SOURCE_DIR}/core/kernels/checkpoint_callback_manager.cc
    ${TF_SOURCE_DIR}/core/kernels/checkpoint_callback_manager.h
    # ${TF_SOURCE_DIR}/core/kernels/clustering_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_all_to_all.cc
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_all_to_all.h
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_broadcaster.cc
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_broadcaster.h
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_gatherer.cc
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_gatherer.h
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_reducer.cc
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl_reducer.h
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl.cc
    ${TF_SOURCE_DIR}/core/kernels/collective_nccl.h
    ${TF_SOURCE_DIR}/core/kernels/collective_ops.cc



    ${TF_SOURCE_DIR}/core/kernels/conditional_accumulator_base_op.cc
    ${TF_SOURCE_DIR}/core/kernels/conditional_accumulator_base_op.h
    ${TF_SOURCE_DIR}/core/kernels/conditional_accumulator_base.cc
    ${TF_SOURCE_DIR}/core/kernels/conditional_accumulator_base.h
    ${TF_SOURCE_DIR}/core/kernels/conditional_accumulator_op.cc
    ${TF_SOURCE_DIR}/core/kernels/conditional_accumulator.h
    ${TF_SOURCE_DIR}/core/kernels/constant_op.cc
    ${TF_SOURCE_DIR}/core/kernels/constant_op.h
    ${TF_SOURCE_DIR}/core/kernels/control_flow_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/control_flow_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_bfloat16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_double.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_float.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_half.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_int_spatial_convolution_backward.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_int_spatial_convolution.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_int.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_uint8.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_uint16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_uint32.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu_uint64.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_2d_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/conv_2d.h
    ${TF_SOURCE_DIR}/core/kernels/conv_3d.h
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_filter_ops_3d.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_filter_ops_launcher.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_filter_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops_3d.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops_bfloat16.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops_double.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops_float.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops_half.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops_int32.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_input_ops.h
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_ops.h
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_shape_utils.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_grad_shape_utils.h
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_3d.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_bfloat16.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_double.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_float.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_fused_double.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_fused_float.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_fused_half.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_fused_image_transform.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_fused_impl.h
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_fused_int8.cc
    # ${TF_SOURCE_DIR}/core/kernels/conv_ops_gpu.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_half.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_impl.h
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_int32.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops_using_gemm.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/conv_ops.h
    ${TF_SOURCE_DIR}/core/kernels/count_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/count_up_to_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/cross_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/cross_op.cc
    ${TF_SOURCE_DIR}/core/kernels/cross_op.h
    ${TF_SOURCE_DIR}/core/kernels/ctc_decoder_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/ctc_loss_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/cudnn_pooling_gpu.cc
    ${TF_SOURCE_DIR}/core/kernels/cudnn_pooling_gpu.h
    # ${TF_SOURCE_DIR}/core/kernels/cudnn_rnn_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_abs.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_acos.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_acosh.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_add_1.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_add_2.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_arg.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_asin.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_asinh.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_atan.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_atan2.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_atanh.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_bitwise_and.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_bitwise_or.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_bitwise_xor.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_ceil.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_clip_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_clip.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_clip.h
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_complex.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_conj.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_cos.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_cosh.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_digamma.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_div.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_equal_to_1.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_equal_to_2.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_erf.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_erfc.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_exp.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_expm1.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_floor_div.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_floor_mod.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_floor.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_abs.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_acos.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_acosh.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_add.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_arg.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_asin.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_asinh.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_atan.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_atan2.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_atanh.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_bitwise_and.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_bitwise_or.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_bitwise_xor.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_ceil.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_complex.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_conj.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_cos.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_cosh.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_digamma.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_div_shard1.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_div_shard2.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_div_shard3.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_div_shard4.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_equal_to.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_erf.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_erfc.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_exp.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_expm1.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_floor_div.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_floor_mod.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_floor.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_greater_equal.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_greater.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_igammas_double.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_igammas_float.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_imag.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_inverse.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_invert.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_isfinite.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_isinf.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_isnan.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_left_shift.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_less_equal.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_less.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_lgamma.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_log.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_log1p.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_logical_and.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_logical_not.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_logical_or.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_maximum.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_minimum.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_mod.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_mul_shard0.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_mul_shard1.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_mul_shard2.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_neg.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_not_equal_to.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_polygamma.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_pow.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_random_grad.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_real.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_right_shift.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_rint.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_round.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_rsqrt.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_select.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_sigmoid.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_sign.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_sin.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_sinh.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_sqrt.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_square.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_squared_difference.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_sub.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_tan.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_tanh.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_xdivy.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_xlog1py.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_xlogy.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/cwise_op_gpu_zeta.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_greater_equal.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_greater.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_igammas.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_imag.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_invert.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_isfinite.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_isinf.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_isnan.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_leakyrelu.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_left_shift.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_less_equal.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_less.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_lgamma.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_log.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_log1p.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_logical_and.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_logical_not.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_logical_or.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_maximum.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_minimum.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_mod.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_mul_1.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_mul_2.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_ndtri_double.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_ndtri_float.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_ndtri.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_neg_1.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_neg_2.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_not_equal_to_1.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_not_equal_to_2.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_pow.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_random_grad.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_real.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_reciprocal.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_right_shift.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_rint.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_round.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_rsqrt.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_select.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_sigmoid.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_sign.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_sin.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_sinh.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_sqrt.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_square.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_squared_difference.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_sub.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_tan.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_tanh.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_xdivy.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_xlog1py.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_xlogy.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_op_zeta.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_ops_common.cc
    ${TF_SOURCE_DIR}/core/kernels/cwise_ops_common.h
    ${TF_SOURCE_DIR}/core/kernels/cwise_ops_gpu_common.cu.h
    ${TF_SOURCE_DIR}/core/kernels/cwise_ops_gpu_gradients.cu.h
    ${TF_SOURCE_DIR}/core/kernels/cwise_ops_gradients.h
    ${TF_SOURCE_DIR}/core/kernels/cwise_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/data_format_ops_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/data_format_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/data_format_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/debug_ops_gpu.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/debug_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/debug_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/decode_compressed_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/decode_csv_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/decode_padded_raw_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/decode_proto_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/decode_raw_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/decode_wav_op.cc
    ${TF_SOURCE_DIR}/core/kernels/deep_conv2d.cc
    ${TF_SOURCE_DIR}/core/kernels/deep_conv2d.h
    # ${TF_SOURCE_DIR}/core/kernels/dense_update_functor_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/dense_update_functor.cc
    ${TF_SOURCE_DIR}/core/kernels/dense_update_functor.h
    ${TF_SOURCE_DIR}/core/kernels/dense_update_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/depthtospace_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/depthtospace_op.cc
    ${TF_SOURCE_DIR}/core/kernels/depthtospace_op.h
    ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_grad_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_op_gpu_bfloat16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_op_gpu_double.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_op_gpu_float.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_op_gpu_half.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_op_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_op.cc
    ${TF_SOURCE_DIR}/core/kernels/depthwise_conv_op.h
    # ${TF_SOURCE_DIR}/core/kernels/dequantize_op.cc
    ${TF_SOURCE_DIR}/core/kernels/deserialize_sparse_string_op.cc
    ${TF_SOURCE_DIR}/core/kernels/deserialize_sparse_variant_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/diag_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/diag_op.cc
    ${TF_SOURCE_DIR}/core/kernels/diag_op.h
    # ${TF_SOURCE_DIR}/core/kernels/dilation_ops_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/dilation_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/dilation_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/dynamic_partition_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/dynamic_partition_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/dynamic_stitch_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/dynamic_stitch_op.cc
    ${TF_SOURCE_DIR}/core/kernels/edit_distance_op.cc
    ${TF_SOURCE_DIR}/core/kernels/eigen_activations.h
    ${TF_SOURCE_DIR}/core/kernels/eigen_attention.h
    ${TF_SOURCE_DIR}/core/kernels/eigen_backward_cuboid_convolutions.h
    ${TF_SOURCE_DIR}/core/kernels/eigen_backward_spatial_convolutions.h
    ${TF_SOURCE_DIR}/core/kernels/eigen_benchmark.h
    ${TF_SOURCE_DIR}/core/kernels/eigen_cuboid_convolution.h
    ${TF_SOURCE_DIR}/core/kernels/eigen_pooling.h
    # ${TF_SOURCE_DIR}/core/kernels/encode_proto_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/encode_wav_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/example_parsing_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/fact_op.cc
    ${TF_SOURCE_DIR}/core/kernels/fake_quant_ops_functor.h
    # ${TF_SOURCE_DIR}/core/kernels/fake_quant_ops_gpu.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/fake_quant_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/fft_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/fifo_queue_op.cc
    ${TF_SOURCE_DIR}/core/kernels/fifo_queue.cc
    ${TF_SOURCE_DIR}/core/kernels/fifo_queue.h

    # ${TF_SOURCE_DIR}/core/kernels/fingerprint_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/fixed_length_record_reader_op.cc
    ${TF_SOURCE_DIR}/core/kernels/fractional_avg_pool_op.cc
    ${TF_SOURCE_DIR}/core/kernels/fractional_max_pool_op.cc
    ${TF_SOURCE_DIR}/core/kernels/fractional_pool_common.cc
    ${TF_SOURCE_DIR}/core/kernels/fractional_pool_common.h
    ${TF_SOURCE_DIR}/core/kernels/function_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/function_ops.h
    ${TF_SOURCE_DIR}/core/kernels/functional_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/fused_batch_norm_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/fused_batch_norm_op.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/fused_batch_norm_op.h
    ${TF_SOURCE_DIR}/core/kernels/fused_eigen_output_kernels.cc
    ${TF_SOURCE_DIR}/core/kernels/fused_eigen_output_kernels.h
    # ${TF_SOURCE_DIR}/core/kernels/gather_functor_batched_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_functor_batched_gpu.cu.h
    ${TF_SOURCE_DIR}/core/kernels/gather_functor_batched.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_functor_batched.h
    # ${TF_SOURCE_DIR}/core/kernels/gather_functor_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_functor_gpu.cu.h
    ${TF_SOURCE_DIR}/core/kernels/gather_functor.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_functor.h
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_0.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_1.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_2.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_3.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_4.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_5.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_6.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl_7.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_cpu_impl.h
    # ${TF_SOURCE_DIR}/core/kernels/gather_nd_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op.cc
    ${TF_SOURCE_DIR}/core/kernels/gather_nd_op.h
    ${TF_SOURCE_DIR}/core/kernels/gather_op.cc
    ${TF_SOURCE_DIR}/core/kernels/gemm_functors.h
    ${TF_SOURCE_DIR}/core/kernels/generate_vocab_remapping_op.cc
    ${TF_SOURCE_DIR}/core/kernels/gpu_device_array_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/gpu_device_array.h
    ${TF_SOURCE_DIR}/core/kernels/gpu_prim_helpers.h
    ${TF_SOURCE_DIR}/core/kernels/gpu_prim.h
    # ${TF_SOURCE_DIR}/core/kernels/gpu_utils.cc
    ${TF_SOURCE_DIR}/core/kernels/gpu_utils.h
    ${TF_SOURCE_DIR}/core/kernels/guarantee_const_op.cc
    ${TF_SOURCE_DIR}/core/kernels/hinge-loss.h
    # ${TF_SOURCE_DIR}/core/kernels/histogram_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/histogram_op.cc
    ${TF_SOURCE_DIR}/core/kernels/histogram_op.h
    ${TF_SOURCE_DIR}/core/kernels/host_constant_op.cc
    ${TF_SOURCE_DIR}/core/kernels/host_constant_op.h
    ${TF_SOURCE_DIR}/core/kernels/identity_n_op.cc
    ${TF_SOURCE_DIR}/core/kernels/identity_n_op.h
    ${TF_SOURCE_DIR}/core/kernels/identity_op.cc
    ${TF_SOURCE_DIR}/core/kernels/identity_op.h
    ${TF_SOURCE_DIR}/core/kernels/identity_reader_op.cc
    ${TF_SOURCE_DIR}/core/kernels/immutable_constant_op.cc
    ${TF_SOURCE_DIR}/core/kernels/immutable_constant_op.h
    # ${TF_SOURCE_DIR}/core/kernels/in_topk_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/in_topk_op.cc
    ${TF_SOURCE_DIR}/core/kernels/in_topk_op.h
    ${TF_SOURCE_DIR}/core/kernels/initializable_lookup_table.cc
    ${TF_SOURCE_DIR}/core/kernels/initializable_lookup_table.h
    # ${TF_SOURCE_DIR}/core/kernels/inplace_ops_functor_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/inplace_ops_functor.h
    ${TF_SOURCE_DIR}/core/kernels/inplace_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/isotonic_regression_op.cc
    ${TF_SOURCE_DIR}/core/kernels/kernel_platform_strings.h
    # ${TF_SOURCE_DIR}/core/kernels/l2loss_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/l2loss_op.cc
    ${TF_SOURCE_DIR}/core/kernels/l2loss_op.h
    ${TF_SOURCE_DIR}/core/kernels/linalg_ops_common.h
    ${TF_SOURCE_DIR}/core/kernels/listdiff_op.cc
    ${TF_SOURCE_DIR}/core/kernels/lmdb_reader_op.cc
    ${TF_SOURCE_DIR}/core/kernels/load_and_remap_matrix_op.cc
    ${TF_SOURCE_DIR}/core/kernels/logging_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/logging_ops.h
    ${TF_SOURCE_DIR}/core/kernels/logistic-loss.h
    ${TF_SOURCE_DIR}/core/kernels/lookup_table_init_op.cc
    ${TF_SOURCE_DIR}/core/kernels/lookup_table_init_op.h
    ${TF_SOURCE_DIR}/core/kernels/lookup_table_op.cc
    ${TF_SOURCE_DIR}/core/kernels/lookup_table_op.h
    ${TF_SOURCE_DIR}/core/kernels/lookup_util.cc
    ${TF_SOURCE_DIR}/core/kernels/lookup_util.h
    ${TF_SOURCE_DIR}/core/kernels/loss.h
    ${TF_SOURCE_DIR}/core/kernels/lrn_op.cc
    ${TF_SOURCE_DIR}/core/kernels/map_kernels.cc
    ${TF_SOURCE_DIR}/core/kernels/map_kernels.h
    ${TF_SOURCE_DIR}/core/kernels/map_stage_op.cc
    ${TF_SOURCE_DIR}/core/kernels/matching_files_op.cc
    ${TF_SOURCE_DIR}/core/kernels/matmul_op_complex.cc
    ${TF_SOURCE_DIR}/core/kernels/matmul_op_fused.cc
    ${TF_SOURCE_DIR}/core/kernels/matmul_op_impl.h
    ${TF_SOURCE_DIR}/core/kernels/matmul_op_real.cc
    ${TF_SOURCE_DIR}/core/kernels/matmul_op.h
    ${TF_SOURCE_DIR}/core/kernels/matmul_util.cc
    ${TF_SOURCE_DIR}/core/kernels/matmul_util.h
    # ${TF_SOURCE_DIR}/core/kernels/maxpooling_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/maxpooling_op_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/maxpooling_op.cc
    ${TF_SOURCE_DIR}/core/kernels/maxpooling_op.h
    # ${TF_SOURCE_DIR}/core/kernels/meta_support.cc
    # ${TF_SOURCE_DIR}/core/kernels/meta_support.h
    ${TF_SOURCE_DIR}/core/kernels/mfcc_dct.cc
    ${TF_SOURCE_DIR}/core/kernels/mfcc_dct.h
    ${TF_SOURCE_DIR}/core/kernels/mfcc_mel_filterbank.cc
    ${TF_SOURCE_DIR}/core/kernels/mfcc_mel_filterbank.h
    ${TF_SOURCE_DIR}/core/kernels/mfcc_op.cc
    ${TF_SOURCE_DIR}/core/kernels/mfcc.cc
    ${TF_SOURCE_DIR}/core/kernels/mfcc.h
    # ${TF_SOURCE_DIR}/core/kernels/multinomial_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/multinomial_op.cc
    ${TF_SOURCE_DIR}/core/kernels/multinomial_op.h
    ${TF_SOURCE_DIR}/core/kernels/mutex_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/nccl_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/nextafter_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/nextafter_op.cc
    ${TF_SOURCE_DIR}/core/kernels/nextafter_op.h
    ${TF_SOURCE_DIR}/core/kernels/no_op.cc
    ${TF_SOURCE_DIR}/core/kernels/no_op.h
    ${TF_SOURCE_DIR}/core/kernels/nth_element_op.cc
    ${TF_SOURCE_DIR}/core/kernels/nth_element_op.h
    ${TF_SOURCE_DIR}/core/kernels/numeric_options_utils.h
    # ${TF_SOURCE_DIR}/core/kernels/one_hot_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/one_hot_op.cc
    ${TF_SOURCE_DIR}/core/kernels/one_hot_op.h
    ${TF_SOURCE_DIR}/core/kernels/ops_util.h
    ${TF_SOURCE_DIR}/core/kernels/pack_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/pad_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/pad_op.cc
    ${TF_SOURCE_DIR}/core/kernels/pad_op.h
    ${TF_SOURCE_DIR}/core/kernels/padding_fifo_queue_op.cc
    ${TF_SOURCE_DIR}/core/kernels/padding_fifo_queue.cc
    ${TF_SOURCE_DIR}/core/kernels/padding_fifo_queue.h
    # ${TF_SOURCE_DIR}/core/kernels/parameterized_truncated_normal_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/parameterized_truncated_normal_op.cc
    ${TF_SOURCE_DIR}/core/kernels/parameterized_truncated_normal_op.h
    ${TF_SOURCE_DIR}/core/kernels/parse_tensor_op.cc
    ${TF_SOURCE_DIR}/core/kernels/partitioned_function_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/partitioned_function_ops.h
    ${TF_SOURCE_DIR}/core/kernels/poisson-loss.h
    # ${TF_SOURCE_DIR}/core/kernels/pooling_ops_3d_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/pooling_ops_3d_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/pooling_ops_3d.cc
    ${TF_SOURCE_DIR}/core/kernels/pooling_ops_3d.h
    ${TF_SOURCE_DIR}/core/kernels/pooling_ops_common_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/pooling_ops_common.cc
    ${TF_SOURCE_DIR}/core/kernels/pooling_ops_common.h
    # ${TF_SOURCE_DIR}/core/kernels/population_count_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/population_count_op.cc
    ${TF_SOURCE_DIR}/core/kernels/population_count_op.h
    ${TF_SOURCE_DIR}/core/kernels/priority_queue_op.cc
    ${TF_SOURCE_DIR}/core/kernels/priority_queue.cc
    ${TF_SOURCE_DIR}/core/kernels/priority_queue.h
    # ${TF_SOURCE_DIR}/core/kernels/quantization_utils.cc
    ${TF_SOURCE_DIR}/core/kernels/quantization_utils.h
    # ${TF_SOURCE_DIR}/core/kernels/quantize_and_dequantize_op_gpu.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantize_and_dequantize_op.cc
    ${TF_SOURCE_DIR}/core/kernels/quantize_and_dequantize_op.h
    # ${TF_SOURCE_DIR}/core/kernels/quantize_down_and_shrink_range.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantize_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_activation_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_add_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_batch_norm_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_bias_add_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_concat_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_conv_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_instance_norm.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_matmul_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_mul_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_pooling_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_reshape_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/quantized_resize_bilinear_op.cc
    ${TF_SOURCE_DIR}/core/kernels/queue_base.cc
    ${TF_SOURCE_DIR}/core/kernels/queue_base.h
    ${TF_SOURCE_DIR}/core/kernels/queue_op.cc
    ${TF_SOURCE_DIR}/core/kernels/queue_op.h
    ${TF_SOURCE_DIR}/core/kernels/queue_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_cross_op.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_fill_empty_rows_op.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_gather_op.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_range_op.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_tensor_from_variant_op.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_tensor_to_sparse_kernel.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_tensor_to_tensor_op.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_tensor_to_variant_op.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_tensor_variant.cc
    ${TF_SOURCE_DIR}/core/kernels/ragged_tensor_variant.h
    ${TF_SOURCE_DIR}/core/kernels/ragged_utils.h
    ${TF_SOURCE_DIR}/core/kernels/random_binomial_op.cc
    ${TF_SOURCE_DIR}/core/kernels/random_binomial_op.h
    ${TF_SOURCE_DIR}/core/kernels/random_index_shuffle_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/random_index_shuffle.cc
    ${TF_SOURCE_DIR}/core/kernels/random_index_shuffle.h
    ${TF_SOURCE_DIR}/core/kernels/random_op_cpu.h
    # ${TF_SOURCE_DIR}/core/kernels/random_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/random_op_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/random_op.cc
    ${TF_SOURCE_DIR}/core/kernels/random_op.h
    ${TF_SOURCE_DIR}/core/kernels/random_ops_util.h
    ${TF_SOURCE_DIR}/core/kernels/random_poisson_op.cc
    ${TF_SOURCE_DIR}/core/kernels/random_poisson_op.h
    ${TF_SOURCE_DIR}/core/kernels/random_shuffle_op.cc
    ${TF_SOURCE_DIR}/core/kernels/random_shuffle_queue_op.cc
    ${TF_SOURCE_DIR}/core/kernels/range_sampler.cc
    ${TF_SOURCE_DIR}/core/kernels/range_sampler.h
    ${TF_SOURCE_DIR}/core/kernels/reader_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/record_input_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/record_yielder.cc
    ${TF_SOURCE_DIR}/core/kernels/record_yielder.h
    # ${TF_SOURCE_DIR}/core/kernels/reduce_join_op.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_gpu_kernels.cu.h
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_all.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_any.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_common_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_common.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_common.h
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_euclidean.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_gpu_bfloat16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_gpu_bool.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_gpu_complex64.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_gpu_complex128.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_gpu_double.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_gpu_float.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_gpu_int.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_half_mean_sum.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/reduction_ops_half_prod_max_min.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_max.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_mean.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_min.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_prod.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops_sum.cc
    ${TF_SOURCE_DIR}/core/kernels/reduction_ops.h
    ${TF_SOURCE_DIR}/core/kernels/redux_functor.h
    ${TF_SOURCE_DIR}/core/kernels/reference_gemm.h
    # ${TF_SOURCE_DIR}/core/kernels/regex_full_match_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/regex_replace_op.cc
    ${TF_SOURCE_DIR}/core/kernels/relu_op_functor.h
    # ${TF_SOURCE_DIR}/core/kernels/relu_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/relu_op.cc
    ${TF_SOURCE_DIR}/core/kernels/relu_op.h
    # ${TF_SOURCE_DIR}/core/kernels/requantization_range_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/requantize.cc
    ${TF_SOURCE_DIR}/core/kernels/reshape_op.cc
    ${TF_SOURCE_DIR}/core/kernels/reshape_op.h
    # ${TF_SOURCE_DIR}/core/kernels/reshape_util_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/reshape_util.cc
    ${TF_SOURCE_DIR}/core/kernels/reshape_util.h
    ${TF_SOURCE_DIR}/core/kernels/resource_variable_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/resource_variable_ops.h
    ${TF_SOURCE_DIR}/core/kernels/resource_variable_util.cc
    ${TF_SOURCE_DIR}/core/kernels/resource_variable_util.h
    ${TF_SOURCE_DIR}/core/kernels/restore_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/reverse_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/reverse_op.cc
    ${TF_SOURCE_DIR}/core/kernels/reverse_op.h
    # ${TF_SOURCE_DIR}/core/kernels/reverse_sequence_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/reverse_sequence_op.cc
    ${TF_SOURCE_DIR}/core/kernels/reverse_sequence_op.h
    # ${TF_SOURCE_DIR}/core/kernels/roll_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/roll_op.cc
    ${TF_SOURCE_DIR}/core/kernels/roll_op.h
    ${TF_SOURCE_DIR}/core/kernels/save_op.cc
    ${TF_SOURCE_DIR}/core/kernels/save_restore_tensor.cc
    ${TF_SOURCE_DIR}/core/kernels/save_restore_tensor.h
    ${TF_SOURCE_DIR}/core/kernels/save_restore_v2_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/scan_ops_gpu_bfloat16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/scan_ops_gpu_double.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/scan_ops_gpu_float.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/scan_ops_gpu_half.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/scan_ops_gpu_int.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/scan_ops_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/scan_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/scan_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/scatter_functor_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_functor_gpu.cu.h
    ${TF_SOURCE_DIR}/core/kernels/scatter_functor.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_functor.h
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_0.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_1.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_2.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_3.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_4.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_5.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_6.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl_7.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_cpu_impl.h
    # ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_op.h
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_util.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_nd_util.h
    # ${TF_SOURCE_DIR}/core/kernels/scatter_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/scatter_op.cc
    ${TF_SOURCE_DIR}/core/kernels/scoped_allocator_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/sdca_internal.cc
    ${TF_SOURCE_DIR}/core/kernels/sdca_internal.h
    ${TF_SOURCE_DIR}/core/kernels/sdca_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/searchsorted_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/searchsorted_op.cc
    ${TF_SOURCE_DIR}/core/kernels/searchsorted_op.h
    # ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_gpu_0.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_gpu_1.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_gpu_2.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_gpu.cu.h
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_impl_1.cc
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_impl_2.cc
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_impl_3.cc
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_impl_3b.cc
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_impl_4.cc
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_impl_5.cc
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops_impl.h
    ${TF_SOURCE_DIR}/core/kernels/segment_reduction_ops.h
    ${TF_SOURCE_DIR}/core/kernels/sendrecv_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/sendrecv_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/sequence_ops_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sequence_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/sequence_ops.h
    ${TF_SOURCE_DIR}/core/kernels/serialize_sparse_op.cc
    ${TF_SOURCE_DIR}/core/kernels/session_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/set_kernels.cc
    ${TF_SOURCE_DIR}/core/kernels/shape_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/shape_ops.h
    ${TF_SOURCE_DIR}/core/kernels/shuffle_common.h
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_1.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_2.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_3.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_4.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_5.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_6.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_7.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl_8.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op_cpu_impl.h
    # ${TF_SOURCE_DIR}/core/kernels/slice_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op.cc
    ${TF_SOURCE_DIR}/core/kernels/slice_op.h
    ${TF_SOURCE_DIR}/core/kernels/smooth-hinge-loss.h
    # ${TF_SOURCE_DIR}/core/kernels/snapshot_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/snapshot_op.cc
    ${TF_SOURCE_DIR}/core/kernels/snapshot_op.h
    # ${TF_SOURCE_DIR}/core/kernels/sobol_op.cc
    ${TF_SOURCE_DIR}/core/kernels/softmax_op_functor.h
    # ${TF_SOURCE_DIR}/core/kernels/softmax_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/softmax_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/softplus_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/softplus_op.cc
    ${TF_SOURCE_DIR}/core/kernels/softplus_op.h
    # ${TF_SOURCE_DIR}/core/kernels/softsign_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/softsign_op.cc
    ${TF_SOURCE_DIR}/core/kernels/softsign_op.h
    # ${TF_SOURCE_DIR}/core/kernels/spacetobatch_functor_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/spacetobatch_functor.cc
    ${TF_SOURCE_DIR}/core/kernels/spacetobatch_functor.h
    ${TF_SOURCE_DIR}/core/kernels/spacetobatch_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/spacetodepth_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/spacetodepth_op.cc
    ${TF_SOURCE_DIR}/core/kernels/spacetodepth_op.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_add_grad_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_add_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/sparse_concat_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_concat_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_concat_op.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_conditional_accumulator_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_conditional_accumulator.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_cross_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_dense_binary_op_shared.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_fill_empty_rows_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_matmul_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_matmul_op.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_reduce_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/sparse_reorder_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_reorder_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_reorder_op.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_reshape_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/sparse_slice_grad_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_slice_grad_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_slice_grad_op.h
    # ${TF_SOURCE_DIR}/core/kernels/sparse_slice_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_slice_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_slice_op.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_softmax_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_sparse_binary_op_shared.cc
    # ${TF_SOURCE_DIR}/core/kernels/sparse_split_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_split_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_split_op.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_tensor_dense_add_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_tensor_dense_add_op.h
    # ${TF_SOURCE_DIR}/core/kernels/sparse_tensor_dense_matmul_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_tensor_dense_matmul_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_tensor_dense_matmul_op.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_tensors_map_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/sparse_to_dense_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_to_dense_op_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/sparse_to_dense_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_utils.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_utils.h
    # ${TF_SOURCE_DIR}/core/kernels/sparse_xent_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_xent_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sparse_xent_op.h
    # ${TF_SOURCE_DIR}/core/kernels/spectrogram_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/spectrogram.cc
    ${TF_SOURCE_DIR}/core/kernels/spectrogram.h

    ${TF_SOURCE_DIR}/core/kernels/squared-loss.h
    ${TF_SOURCE_DIR}/core/kernels/stack_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/stack.cc
    ${TF_SOURCE_DIR}/core/kernels/stack.h
    ${TF_SOURCE_DIR}/core/kernels/stage_op.cc
    ${TF_SOURCE_DIR}/core/kernels/stateful_random_ops_cpu_gpu.h
    # ${TF_SOURCE_DIR}/core/kernels/stateful_random_ops_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/stateful_random_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/stateful_random_ops.h
    # ${TF_SOURCE_DIR}/core/kernels/stateless_random_gamma_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/stateless_random_gamma_op.cc
    ${TF_SOURCE_DIR}/core/kernels/stateless_random_gamma_op.h
    ${TF_SOURCE_DIR}/core/kernels/stateless_random_ops_v2_util.h
    ${TF_SOURCE_DIR}/core/kernels/stateless_random_ops_v2.cc
    ${TF_SOURCE_DIR}/core/kernels/stateless_random_ops_v2.h
    ${TF_SOURCE_DIR}/core/kernels/stateless_random_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/stateless_random_ops.h
    ${TF_SOURCE_DIR}/core/kernels/stateless_shuffle.cc
    ${TF_SOURCE_DIR}/core/kernels/stochastic_cast_op.cc
    ${TF_SOURCE_DIR}/core/kernels/stochastic_cast_op.h
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_define_grad.cc
    # ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_gpu_bool.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_gpu_complex.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_gpu_impl.h
    # ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_gpu_int.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_gpu_number_types.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_impl.h
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_0.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_1.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_2.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_3.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_4.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_5.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_6.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_7.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op_inst_8.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op.cc
    ${TF_SOURCE_DIR}/core/kernels/strided_slice_op.h
    ${TF_SOURCE_DIR}/core/kernels/string_format_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_join_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_length_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_lower_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_ngrams_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_split_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_strip_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_to_hash_bucket_fast_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_to_hash_bucket_fast_op.h
    ${TF_SOURCE_DIR}/core/kernels/string_to_hash_bucket_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_to_hash_bucket_op.h
    ${TF_SOURCE_DIR}/core/kernels/string_to_number_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_upper_op.cc
    ${TF_SOURCE_DIR}/core/kernels/string_util.cc
    ${TF_SOURCE_DIR}/core/kernels/string_util.h
    ${TF_SOURCE_DIR}/core/kernels/substr_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/summary_audio_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/summary_image_op.cc
    ${TF_SOURCE_DIR}/core/kernels/summary_interface.h
    # ${TF_SOURCE_DIR}/core/kernels/summary_kernels.cc
    # ${TF_SOURCE_DIR}/core/kernels/summary_tensor_op.cc
    ${TF_SOURCE_DIR}/core/kernels/sync_ops.cc


    ${TF_SOURCE_DIR}/core/kernels/text_line_reader_op.cc
    ${TF_SOURCE_DIR}/core/kernels/tf_record_reader_op.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_bfloat16.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_bool.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_complex64.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_complex128.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_double.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_float.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_half.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_int8.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_int16.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_int32.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_int64.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_tstring.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_uint8.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_uint32.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_uint64.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu_variant.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_cpu.h
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_bfloat16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_bool.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_complex64.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_complex128.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_double.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_float.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_half.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_int16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_int32.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu_int64.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/tile_functor_sycl.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_functor.h
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl_1.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl_2.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl_3.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl_4.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl_5.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl_6.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl_7.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_cpu_impl.h
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_1.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_2.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_3.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_4.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_5.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_6.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_7.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl_8.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_gpu_impl.h
    ${TF_SOURCE_DIR}/core/kernels/tile_ops_impl.h
    ${TF_SOURCE_DIR}/core/kernels/tile_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_bfloat16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_double.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_float.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_half.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_int8.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_int16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_int32.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_int64.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_uint8.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_uint16.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_uint32.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu_uint64.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/topk_op_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/topk_op.cc
    ${TF_SOURCE_DIR}/core/kernels/topk_op.h
    # ${TF_SOURCE_DIR}/core/kernels/training_op_helpers.cc
    ${TF_SOURCE_DIR}/core/kernels/training_op_helpers.h
    # ${TF_SOURCE_DIR}/core/kernels/training_ops_gpu.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/training_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/training_ops.h
    ${TF_SOURCE_DIR}/core/kernels/transpose_functor_cpu.cc
    # ${TF_SOURCE_DIR}/core/kernels/transpose_functor_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/transpose_functor.h
    ${TF_SOURCE_DIR}/core/kernels/transpose_op.cc
    ${TF_SOURCE_DIR}/core/kernels/transpose_op.h
    ${TF_SOURCE_DIR}/core/kernels/typed_conditional_accumulator_base.h
    ${TF_SOURCE_DIR}/core/kernels/typed_queue.h
    ${TF_SOURCE_DIR}/core/kernels/unary_ops_composition.cc
    # ${TF_SOURCE_DIR}/core/kernels/unicode_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/unicode_script_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/unique_op_gpu_0.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/unique_op_gpu_1.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/unique_op_gpu_2.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/unique_op_gpu_3.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/unique_op_gpu.cu.h
    ${TF_SOURCE_DIR}/core/kernels/unique_op.cc
    ${TF_SOURCE_DIR}/core/kernels/unpack_op.cc
    ${TF_SOURCE_DIR}/core/kernels/unravel_index_op.cc
    ${TF_SOURCE_DIR}/core/kernels/unsorted_segment_join_op.cc
    ${TF_SOURCE_DIR}/core/kernels/variable_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/variable_ops.h
    ${TF_SOURCE_DIR}/core/kernels/variant_ops_util.cc
    ${TF_SOURCE_DIR}/core/kernels/variant_ops_util.h
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_1.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_2.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_3.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_4.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_5.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_6.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_7.cu.cc
    # ${TF_SOURCE_DIR}/core/kernels/where_op_gpu_impl_8.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/where_op_gpu.cu.h
    ${TF_SOURCE_DIR}/core/kernels/where_op.cc
    ${TF_SOURCE_DIR}/core/kernels/where_op.h
    # ${TF_SOURCE_DIR}/core/kernels/whole_file_read_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/winograd_transform.h
    # ${TF_SOURCE_DIR}/core/kernels/word2vec_kernels.cc
    # ${TF_SOURCE_DIR}/core/kernels/xent_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/xent_op.cc
    ${TF_SOURCE_DIR}/core/kernels/xent_op.h
]]
    ${TF_SOURCE_DIR}/core/kernels/composite_tensor_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/composite_tensor_variant.cc
    ${TF_SOURCE_DIR}/core/kernels/composite_tensor_variant.h
    ${TF_SOURCE_DIR}/core/kernels/concat_lib_cpu.cc
    ${TF_SOURCE_DIR}/core/kernels/concat_lib_cpu.h
    # ${TF_SOURCE_DIR}/core/kernels/concat_lib_gpu_impl.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/concat_lib_gpu.cc
    ${TF_SOURCE_DIR}/core/kernels/concat_lib_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/concat_lib.h
    ${TF_SOURCE_DIR}/core/kernels/concat_op.cc
    # ${TF_SOURCE_DIR}/core/kernels/filesystem_ops.cc
    # ${TF_SOURCE_DIR}/core/kernels/fill_empty_rows_functor_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/fill_empty_rows_functor.cc
    ${TF_SOURCE_DIR}/core/kernels/fill_empty_rows_functor.h
    ${TF_SOURCE_DIR}/core/kernels/fill_functor.cc
    # ${TF_SOURCE_DIR}/core/kernels/fill_functor.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/fill_functor.h
    ${TF_SOURCE_DIR}/core/kernels/list_kernels.cc
    # ${TF_SOURCE_DIR}/core/kernels/list_kernels.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/list_kernels.h

    ${TF_SOURCE_DIR}/core/kernels/split_lib_cpu.cc
    # ${TF_SOURCE_DIR}/core/kernels/split_lib_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/split_lib_gpu.h
    ${TF_SOURCE_DIR}/core/kernels/split_lib.h
    ${TF_SOURCE_DIR}/core/kernels/split_op.cc
    ${TF_SOURCE_DIR}/core/kernels/split_v_op.cc

    ${TF_SOURCE_DIR}/core/kernels/tensor_array_ops.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_array.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_array.h
    ${TF_SOURCE_DIR}/core/kernels/tensor_cord.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_cord.h
    ${TF_SOURCE_DIR}/core/kernels/tensor_flag_utils.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_flag_utils.h
    ${TF_SOURCE_DIR}/core/kernels/tensor_list_util.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_list_util.h
    ${TF_SOURCE_DIR}/core/kernels/tensor_list.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_list.h
    ${TF_SOURCE_DIR}/core/kernels/tensor_map.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_map.h
    # ${TF_SOURCE_DIR}/core/kernels/tensor_to_hash_bucket_op_gpu.cu.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_to_hash_bucket_op.cc
    ${TF_SOURCE_DIR}/core/kernels/tensor_to_hash_bucket_op.h


    # ${TF_SOURCE_DIR}/core/ops/list_ops.cc
    ${TF_SOURCE_DIR}/core/ops/*.cc



    ${TF_SOURCE_DIR}/core/nccl/*.cc
    ${TF_SOURCE_DIR}/core/graph/*.cc
    ${TF_SOURCE_DIR}/core/tfrt/fallback/op_kernel_runner.cc
    ${TF_SOURCE_DIR}/core/lib/strings/*.cc
    ${TF_SOURCE_DIR}/core/lib/core/arena.cc
    ${TF_SOURCE_DIR}/core/lib/wav/*.cc
    ${TF_SOURCE_DIR}/compiler/jit/defs.cc
    ${TF_SOURCE_DIR}/c/eager/*.cc
    ${TF_SOURCE_DIR}/c/tf_datatype.cc
    ${TF_SOURCE_DIR}/c/tf_tensor.cc
    ${TF_SOURCE_DIR}/c/tf_*.cc

    # autogenerated protobuf
    ${TF_SOURCE_DIR}/core/*.pb.cc
    ${TF_SOURCE_DIR}/core/*.pb.h

    # third party
    # ${TF_SOURCE_DIR}/../third_party/ducc/*.h
    # ${TF_SOURCE_DIR}/../third_party/ducc/*.cc
)

add_library(${PROJECT_NAME} STATIC ${TF_CORE_SOURCES})

if (MSVC)    
    add_compile_definitions(${PROJECT_NAME} PRIVATE TF_COMPILE_LIBRARY)
    target_compile_options(${PROJECT_NAME}
    PUBLIC
        "/Zc:preprocessor"
    )
endif()

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${TENSORFLOW_SOURCE_DIR}
PRIVATE
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    ${TF_CORE_PROTOBUF_LIB}
    tsl-lib-interface
PRIVATE
    zlibstatic
    $<$<PLATFORM_ID:Windows>:ws2_32>
    Eigen3::Eigen
    absl_statusor
    absl::check
    absl::log
    ${Protobuf_LIBRARIES}
)


set(PROJECT_INTERFACE "${PROJECT_NAME}-interface")
add_library(${PROJECT_INTERFACE} INTERFACE)

if (MSVC)
    target_compile_options(${PROJECT_INTERFACE}
    INTERFACE
        "/Zc:preprocessor"
    )
endif()

target_include_directories(${PROJECT_INTERFACE} INTERFACE ${TENSORFLOW_SOURCE_DIR})
target_link_libraries(${PROJECT_INTERFACE} INTERFACE tsl-lib-interface)
