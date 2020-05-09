//
// Created by murmur wheel on 2020/4/26.
//

#include <vkut/framegraph.h>

namespace vkut {
void example() {
    FgRenderPass rp;
    struct RT {
        uint32_t color;
        uint32_t ds;
    };
    RT rt;
    rt.color = rp.create_attachment();
    rt.ds = rp.create_attachment();

    rp.add_task(
        [&rt](FgTaskBuilder &builder) {
            builder.add_color_attachment(rt.color);
            builder.add_input_attachment(rt.color, 0, 0);
        },
        [](FgPipelineBuilder &builder) {
            builder.set_primitive_topology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
            builder.create();
        },
        [](VkCommandBuffer cmd) {});

    rp.compile();
    rp.execute();
}
}
