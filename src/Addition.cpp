#include "plugin.hpp"

struct Addition : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(IN_A_INPUTS, 8),
		ENUMS(IN_B_INPUTS, 8),
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUT_OUTPUTS, 8),
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Addition() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		for (int i = 0; i < 8; i++) {
			configInput(IN_A_INPUTS + i, string::f("Row %d A", i + 1));
			configInput(IN_B_INPUTS + i, string::f("Row %d B", i + 1));
			configOutput(OUT_OUTPUTS + i, string::f("Row %d", i + 1));
		}
	}

	void process(const ProcessArgs& args) override {
		float in_A[16] = {10.f};
		float in_B[16] = {0.f};
		int channels = 1;

		for (int i = 0; i < 8; i++) {
			// Get input
			if (inputs[IN_A_INPUTS + i].isConnected()) {
				channels = inputs[IN_A_INPUTS + i].getChannels();
				inputs[IN_A_INPUTS + i].readVoltages(in_A);
			}

			if (inputs[IN_B_INPUTS + i].isConnected()) {
				channels = inputs[IN_B_INPUTS + i].getChannels();
				inputs[IN_B_INPUTS + i].readVoltages(in_B);
			}

			if (outputs[OUT_OUTPUTS + i].isConnected()) {
				// Apply gain
				float out[16];
				for (int c = 0; c < channels; c++) {
					out[c] = in_A[c] + in_B[c];
				}

				// Set output
				outputs[OUT_OUTPUTS + i].setChannels(channels);
				outputs[OUT_OUTPUTS + i].writeVoltages(out);
			}
		}
	}
};


struct AdditionWidget : ModuleWidget {
	AdditionWidget(Addition* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Addition.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 21.968)), module, Addition::IN_A_INPUTS + 0));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 34.982)), module, Addition::IN_A_INPUTS + 1));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 48.004)), module, Addition::IN_A_INPUTS + 2));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 61.026)), module, Addition::IN_A_INPUTS + 3));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 74.048)), module, Addition::IN_A_INPUTS + 4));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 87.07)), module, Addition::IN_A_INPUTS + 5));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 100.093)), module, Addition::IN_A_INPUTS + 6));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.331, 113.115)), module, Addition::IN_A_INPUTS + 7));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 21.968)), module, Addition::IN_B_INPUTS + 0));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 34.982)), module, Addition::IN_B_INPUTS + 1));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 48.004)), module, Addition::IN_B_INPUTS + 2));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 61.026)), module, Addition::IN_B_INPUTS + 3));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 74.048)), module, Addition::IN_B_INPUTS + 4));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 87.07)), module, Addition::IN_B_INPUTS + 5));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 100.093)), module, Addition::IN_B_INPUTS + 6));
		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(20.351, 113.115)), module, Addition::IN_B_INPUTS + 7));

		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 21.968)), module, Addition::OUT_OUTPUTS + 0));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 34.982)), module, Addition::OUT_OUTPUTS + 1));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 48.004)), module, Addition::OUT_OUTPUTS + 2));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 61.026)), module, Addition::OUT_OUTPUTS + 3));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 74.048)), module, Addition::OUT_OUTPUTS + 4));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 87.07)), module, Addition::OUT_OUTPUTS + 5));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 100.093)), module, Addition::OUT_OUTPUTS + 6));
		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(33.371, 113.115)), module, Addition::OUT_OUTPUTS + 7));
	}
};


Model* modelAddition = createModel<Addition, AdditionWidget>("Addition");
