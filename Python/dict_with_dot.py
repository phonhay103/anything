class args_dict(dict):
    __getattr__ = dict.get
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__

args = args_dict({'im_dim':64, 'latent_dim':200, 'kernel_size':4, 'strides':2})
print(args.im_dim, args.latent_dim, args.kernel_size, args.strides)